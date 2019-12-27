#include <stdlib.h>
#include <RSE/RSE_private.h>

#define zalloc(sz) calloc(1, sz)

RSE_API RseContext* rseCreateContext(int frequency, int channels)
{
    RseContext* ctx;

    ctx = zalloc(sizeof(*ctx));
    if (!ctx)
        return NULL;

    ctx->outFreq = frequency;
    ctx->genFreq = frequency * 4;
    ctx->channelCount = channels;
    ctx->channels = zalloc(sizeof(RseChannel) * channels);
    if (!ctx->channels)
    {
        free(ctx);
        return NULL;
    }

    return ctx;
}

RSE_API void rseDestroyContext(RseContext* ctx)
{
    if (ctx)
    {
        free(ctx->channels);
        free(ctx);
    }
}
