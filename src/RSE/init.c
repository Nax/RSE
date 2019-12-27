#include <stdlib.h>
#include <RSE/RSE_private.h>

#define zalloc(sz) calloc(1, sz)

RSE_API RseContext* rseCreateContext(int frequency, int channels)
{
    int16_t tmp[BUFFER_SIZE];
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

    ctx->alDevice = alcOpenDevice(NULL);
    ctx->alContext = alcCreateContext(ctx->alDevice, NULL);
    alcMakeContextCurrent(ctx->alContext);
    alGenSources(1, &ctx->alSource);
    alGenBuffers(BUFFER_COUNT, ctx->alBuffers);
    memset(tmp, 0, sizeof(tmp));
    for (int i = 0; i < BUFFER_COUNT; ++i)
    {
        alBufferData(ctx->alBuffers[i], AL_FORMAT_MONO16, tmp, BUFFER_SIZE * sizeof(int16_t), ctx->outFreq);
    }
    alSourceQueueBuffers(ctx->alSource, BUFFER_COUNT, ctx->alBuffers);
    alSourcePlay(ctx->alSource);

#if defined(WIN32) || defined(_WIN32)
    ctx->workerThread = CreateThread(NULL, 0, &rseWorkerMain, ctx, 0, 0);
#endif

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
