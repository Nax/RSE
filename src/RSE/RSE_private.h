#ifndef RSE_PRIVATE_H
#define RSE_PRIVATE_H 1

#include <RSE/RSE.h>

typedef struct
{
    float freq;
} RseChannel;

struct RseContext_
{
    int channelCount;
    int outFreq;
    int genFreq;

    RseChannel* channels;
};

#endif
