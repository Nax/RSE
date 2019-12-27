#ifndef RSE_H
#define RSE_H 1

#include <RSE/abi.h>

#define RSE_WAVE_NULL       0
#define RSE_WAVE_SINE       1
#define RSE_WAVE_SQUARE     2
#define RSE_WAVE_TRIANGLE   3
#define RSE_WAVE_SAWTOOTH   4
#define RSE_WAVE_NOISE      5

typedef struct RseContext_ RseContext;

/*
 * init
 */
RSE_API RseContext* rseCreateContext(int frequency, int channels);
RSE_API void        rseDestroyContext(RseContext* ctx);

/*
 * channel
 */
RSE_API void rseChannelType(RseContext* ctx, int ch, int type);
RSE_API void rseChannelFrequency(RseContext* ctx, int ch, float freq);
RSE_API void rseChannelGain(RseContext* ctx, int ch, float gain);

#endif
