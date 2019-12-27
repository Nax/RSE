#ifndef RSE_PRIVATE_H
#define RSE_PRIVATE_H 1

#include <stdint.h>

#if defined(WIN32) || defined(_WIN32)
# include <windows.h>
typedef HANDLE RseThread;
#endif

#include <al.h>
#include <alc.h>
#include <alext.h>
#include <RSE/RSE.h>

#define BUFFER_SIZE     1024
#define BUFFER_COUNT    4

typedef struct
{
    int     type;
    float   gain;
    float   clock;
    float   clockInc;
} RseChannel;

struct RseContext_
{
    int channelCount;
    int outFreq;
    int genFreq;

    ALCdevice*  alDevice;
    ALCcontext* alContext;
    ALuint      alSource;
    ALuint      alBuffers[BUFFER_COUNT];

    RseChannel* channels;
    RseThread   workerThread;
};

#if defined(WIN32) || defined(_WIN32)
DWORD WINAPI rseWorkerMain(LPVOID arg);
#endif

void rseMix(RseContext* ctx, int16_t* buffer);
void rseGenWaveSquare(RseContext* ctx, RseChannel* ch, float* buffer);

#endif
