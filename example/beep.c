#include <windows.h>
#include <RSE/RSE.h>

int main(void)
{
    RseContext* ctx;

    ctx = rseCreateContext(48000, 16);
    rseChannelType(ctx, 0, RSE_WAVE_SQUARE);
    rseChannelFrequency(ctx, 0, 110.f);
    rseChannelGain(ctx, 0, 1.f);
    Sleep(10000);
    rseDestroyContext(ctx);
    return 0;
}
