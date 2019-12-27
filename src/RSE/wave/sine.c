#include <math.h>
#include <RSE/RSE_private.h>

#define PI 3.14159265359f

void rseGenWaveSine(RseContext* ctx, RseChannel* ch, float* buffer)
{
    float v;

    for (int i = 0; i < BUFFER_SIZE_SRC; ++i)
    {
        v = sinf(ch->clock * PI * 2.f);
        ch->clock += ch->freq.value;
        if (ch->clock >= 1.f)
            ch->clock -= 1.f;

        buffer[i] = v * ch->gain.value;
    }
}
