#include <RSE/RSE_private.h>

static void rseModulableFixed(RseModulable* m, float value)
{
    m->value = value;
    m->source = value;
    m->target = value;
    m->mod = 0.f;
    m->acc = 0.f;
}

static void rseModulableDynamic(RseContext* ctx, RseModulable* m, float target, float mod, int repeat)
{
    m->target = target;
    m->mod = (BUFFER_SIZE_SRC / (ctx->genFreq * mod));
    m->acc = 0.f;
    m->repeat = repeat;
}

RSE_API void rseChannelType(RseContext* ctx, int ch, int type)
{
    RseChannel* c;

    c = ctx->channels + ch;
    c->type = type;
    c->clock = 0;
    rseModulableFixed(&c->duty, 0.5f);
}

RSE_API void rseChannelFrequency(RseContext* ctx, int ch, float freq)
{
    RseChannel* c;

    c = ctx->channels + ch;
    rseModulableFixed(&c->freq, freq / ctx->outFreq);
}

RSE_API void rseChannelFrequencyModulation(RseContext* ctx, int ch, float targetFreq, float time, int repeat)
{
    RseChannel* c;

    c = ctx->channels + ch;
    rseModulableDynamic(ctx, &c->freq, targetFreq / ctx->outFreq, time, repeat);
}

RSE_API void rseChannelGain(RseContext* ctx, int ch, float gain)
{
    RseChannel* c;

    c = ctx->channels + ch;
    rseModulableFixed(&c->gain, gain);
}

RSE_API void rseChannelGainModulation(RseContext* ctx, int ch, float targetGain, float time, int repeat)
{
    RseChannel* c;

    c = ctx->channels + ch;
    rseModulableDynamic(ctx, &c->gain, targetGain, time, repeat);
}

RSE_API void rseChannelDuty(RseContext* ctx, int ch, float duty)
{
    RseChannel* c;

    c = ctx->channels + ch;
    rseModulableFixed(&c->duty, duty);
}

RSE_API void rseChannelDutyModulation(RseContext* ctx, int ch, float targetDuty, float time, int repeat)
{
    RseChannel* c;

    c = ctx->channels + ch;
    rseModulableDynamic(ctx, &c->duty, targetDuty, time, repeat);
}
