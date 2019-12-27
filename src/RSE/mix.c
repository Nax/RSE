#include <RSE/RSE_private.h>

static float lerp(float a, float b, float x)
{
    return (1.f - x) * a + x * b;
}

static int16_t conv16(float sample)
{
    if (sample > 1.f)
        return 32767;
    else if (sample < -1.f)
        return -32768;
    return (int16_t)(sample * 32767);
}

static void rseModulate(RseModulable* m)
{
    m->value = lerp(m->source, m->target, m->acc);
    m->acc += m->mod;
    if (m->acc >= 1.f)
    {
        if (m->repeat)
            m->acc -= 1.f;
        else
        {
            m->mod = 0.f;
            m->acc = 0.f;
            m->source = m->target;
            m->value = m->target;
        }
    }
}

static void rseFilter(float* buffer, size_t size, RseFilter* filter)
{
    static const float kGain = 1.677001565f;

    for (size_t i = 0; i < size; ++i)
    {
        filter->xv[0] = filter->xv[1];
        filter->xv[1] = filter->xv[2];
        filter->xv[2] = filter->xv[3];
        filter->xv[3] = filter->xv[4];
        filter->xv[4] = buffer[i] / kGain;

        filter->yv[0] = filter->yv[1];
        filter->yv[1] = filter->yv[2];
        filter->yv[2] = filter->yv[3];
        filter->yv[3] = filter->yv[4];

        filter->yv[4] = (
            filter->xv[0] + filter->xv[4]
            + 4 * (filter->xv[1] + filter->xv[3])
            + 6 * filter->xv[2]
            + (-0.3555773823f * filter->yv[0])
            + (-1.7861066002f * filter->yv[1])
            + (-3.4223095294f * filter->yv[2])
            + (-2.9768443337f * filter->yv[3])
        );

        buffer[i] = filter->yv[4];
    }
}

static void rseDecimate(float* buffer, size_t size)
{
    for (size_t i = 0; i < size / 2; ++i)
    {
        buffer[i] = buffer[i * 2];
    }
}

void rseMix(RseContext* ctx, int16_t* buffer)
{
    float master[BUFFER_SIZE_SRC];
    float tmp[BUFFER_SIZE_SRC];

    memset(master, 0, sizeof(master));

    for (int c = 0; c < ctx->channelCount; ++c)
    {
        RseChannel* ch = ctx->channels + c;
        switch (ch->type)
        {
        case RSE_WAVE_NULL:
            memset(tmp, 0, sizeof(tmp));
            break;
        case RSE_WAVE_SQUARE:
            rseGenWaveSquare(ctx, ch, tmp);
            break;
        case RSE_WAVE_TRIANGLE:
            rseGenWaveTriangle(ctx, ch, tmp);
            break;
        case RSE_WAVE_SINE:
            rseGenWaveSine(ctx, ch, tmp);
            break;
        case RSE_WAVE_SAWTOOTH:
            rseGenWaveSawtooth(ctx, ch, tmp);
            break;
        case RSE_WAVE_NOISE:
            rseGenWaveNoise(ctx, ch, tmp);
            break;
        }

        for (int i = 0; i < BUFFER_SIZE_SRC; ++i)
        {
            master[i] += tmp[i];
        }

        rseModulate(&ch->freq);
        rseModulate(&ch->gain);
        rseModulate(&ch->duty);
    }

    for (int i = 0; i < OVERSAMPLING_STEPS; ++i)
    {
        rseFilter(master, BUFFER_SIZE_SRC / (1 << i), ctx->filters + i);
        rseDecimate(master, BUFFER_SIZE_SRC / (1 << i));
    }

    for (int i = 0; i < BUFFER_SIZE_DST; ++i)
    {
        buffer[i] = conv16(master[i]);
    }
}
