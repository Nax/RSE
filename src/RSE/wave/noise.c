#include <RSE/RSE_private.h>

static const float kNoise[] = {
#include "noise.inc"
};

static unsigned kNoiseCount = sizeof(kNoise) / sizeof(*kNoise);

void rseGenWaveNoise(RseContext* ctx, RseChannel* ch, float* buffer)
{
    float v;

    for (int i = 0; i < BUFFER_SIZE_SRC; ++i)
    {
        v = kNoise[(unsigned)(ch->clock * 16777216) % kNoiseCount];
        ch->clock += ch->freq.value;
        if (ch->clock >= 1.f)
            ch->clock -= 1.f;

        buffer[i] = v * ch->gain.value;
    }
}
