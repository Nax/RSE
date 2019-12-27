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

#define OVERSAMPLING    1
#define BUFFER_SIZE_DST 1024
#define BUFFER_SIZE_SRC 1024 * OVERSAMPLING
#define BUFFER_COUNT    4

typedef struct
{
    float       value;
    float       source;
    float       target;
    float       mod;
    float       acc;
    unsigned    repeat:1;
} RseModulable;

typedef struct
{
    int             type;
    float           clock;
    RseModulable    gain;
    RseModulable    freq;
    RseModulable    duty;
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
void rseGenWaveTriangle(RseContext* ctx, RseChannel* ch, float* buffer);
void rseGenWaveSine(RseContext* ctx, RseChannel* ch, float* buffer);
void rseGenWaveSawtooth(RseContext* ctx, RseChannel* ch, float* buffer);
void rseGenWaveNoise(RseContext* ctx, RseChannel* ch, float* buffer);

#endif
