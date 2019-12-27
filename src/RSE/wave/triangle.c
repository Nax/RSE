#include <RSE/RSE_private.h>

void rseGenWaveTriangle(RseContext* ctx, RseChannel* ch, float* buffer)
{
    float v;

    for (int i = 0; i < BUFFER_SIZE_SRC; ++i)
    {
        if (ch->clock < 0.5f)
        {
            v = ch->clock * 2.f;
        }
        else
        {
            v = (1.f - ch->clock) * 2.f;
        }
        v = (v - 0.5f) * 2.f;
        ch->clock += ch->freq.value;
        if (ch->clock >= 1.f)
            ch->clock -= 1.f;

        buffer[i] = v * ch->gain.value;
    }
}
