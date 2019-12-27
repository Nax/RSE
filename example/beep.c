#include <windows.h>
#include <RSE/RSE.h>

int main(void)
{
    RseContext* ctx;

    ctx = rseCreateContext(48000, 16);
    rseChannelType(ctx, 0, RSE_WAVE_SQUARE);
    rseChannelFrequency(ctx, 0, 440.f);
    rseChannelGain(ctx, 0, 0.8f);
    rseChannelDutyModulation(ctx, 0, 0.9f, 5.f, 1);
    rseChannelFrequencyModulation(ctx, 0, 880.f, 0.1f, 1);
    Sleep(20000);
    rseDestroyContext(ctx);
    return 0;
}
