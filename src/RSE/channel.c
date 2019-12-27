#include <RSE/RSE_private.h>

RSE_API void rseChannelType(RseContext* ctx, int ch, int type)
{
    RseChannel* c;

    c = ctx->channels + ch;
    c->type = type;
    c->clock = 0;
}

RSE_API void rseChannelFrequency(RseContext* ctx, int ch, float freq)
{
    RseChannel* c;

    c = ctx->channels + ch;
    c->clockInc = freq / ctx->outFreq;
}

RSE_API void rseChannelGain(RseContext* ctx, int ch, float gain)
{
    RseChannel* c;

    c = ctx->channels + ch;
    c->gain = gain;
}
