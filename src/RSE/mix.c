#include <RSE/RSE_private.h>

static int16_t conv16(float sample)
{
    if (sample > 1.f)
        return 32767;
    else if (sample < -1.f)
        return -32768;
    return (int16_t)(sample * 32767);
}

void rseMix(RseContext* ctx, int16_t* buffer)
{
    float master[BUFFER_SIZE];
    float tmp[BUFFER_SIZE];

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

        for (int i = 0; i < BUFFER_SIZE; ++i)
        {
            master[i] += tmp[i];
        }
    }

    for (int i = 0; i < BUFFER_SIZE; ++i)
    {
        buffer[i] = conv16(master[i]);
    }
}
