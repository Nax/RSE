#include <RSE/RSE_private.h>

void rseGenWaveTriangle(RseContext* ctx, RseChannel* ch, float* buffer)
{
    float v;

    for (int i = 0; i < BUFFER_SIZE; ++i)
    {
        v = (ch->clock - 0.5f) * 2.f;
        ch->clock += ch->clockInc;
        if (ch->clock >= 1.f)
            ch->clock -= 1.f;

        buffer[i] = v * ch->gain;
    }
}
