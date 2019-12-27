#include <stdio.h>
#include <RSE/RSE_private.h>

static void workerManageBuffers(RseContext* ctx)
{
    int16_t tmp[BUFFER_SIZE_DST];
    ALuint processed;
    ALuint playing;
    ALuint buf;

    for (;;)
    {
        alGetSourcei(ctx->alSource, AL_BUFFERS_PROCESSED, &processed);
        if (!processed)
            break;
        alSourceUnqueueBuffers(ctx->alSource, 1, &buf);
        rseMix(ctx, tmp);
        alBufferData(buf, AL_FORMAT_MONO16, tmp, BUFFER_SIZE_DST * 2, ctx->outFreq);
        alSourceQueueBuffers(ctx->alSource, 1, &buf);
        alGetSourcei(ctx->alSource, AL_SOURCE_STATE, &playing);
        if (playing != AL_PLAYING)
        {
            alSourcePlay(ctx->alSource);
        }
    }
}

#if defined(WIN32) || defined(_WIN32)
DWORD WINAPI rseWorkerMain(LPVOID arg)
#endif
{
    RseContext* ctx;

    ctx = (RseContext*)arg;
    alcMakeContextCurrent(ctx->alContext);
    for (;;)
    {
        Sleep(50);
        workerManageBuffers(ctx);
    }
    return 0;
}
