#include <math.h>
#include <RSE/RSE_private.h>

#define PI 3.14159265359f

void rseGenWaveSawtooth(RseContext* ctx, RseChannel* ch, float* buffer)
{
    float v;

    for (int i = 0; i < BUFFER_SIZE; ++i)
    {
        v = ch->clock;
        ch->clock += ch->clockInc;
        if (ch->clock >= 1.f)
            ch->clock -= 1.f;

        buffer[i] = v * ch->gain;
    }
}
