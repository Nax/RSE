#include <RSE/RSE_private.h>

void rseGenWaveSquare(RseContext* ctx, RseChannel* ch, float* buffer)
{
    float v;

    for (int i = 0; i < BUFFER_SIZE_SRC; ++i)
    {
        v = (ch->clock < ch->duty.value) ? -1.f : 1.f;
        ch->clock += ch->freq.value;
        if (ch->clock >= 1.f)
            ch->clock -= 1.f;

        buffer[i] = v * ch->gain.value;
    }
}
