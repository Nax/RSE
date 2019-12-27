#include <windows.h>
#include <RSE/RSE.h>

int main(void)
{
    RseContext* ctx;

    ctx = rseCreateContext(48000, 16);
    rseChannelFrequency(ctx, 0, 440.f);
    rseChannelGain(ctx, 0, 0.8f);
    rseChannelType(ctx, 0, RSE_WAVE_SINE);
    Sleep(2000);
    rseDestroyContext(ctx);
    return 0;
}
