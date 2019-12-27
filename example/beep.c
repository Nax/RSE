#include <windows.h>
#include <RSE/RSE.h>

int main(void)
{
    RseContext* ctx;

    ctx = rseCreateContext(48000, 16);
    rseChannelType(ctx, 0, RSE_WAVE_TRIANGLE);
    rseChannelFrequency(ctx, 0, 440.f);
    rseChannelFrequencyModulation(ctx, 0, 880.f * 2, 0.125f, 1);
    rseChannelGain(ctx, 0, 0.8f);
    rseChannelType(ctx, 1, RSE_WAVE_NOISE);
    rseChannelFrequency(ctx, 1, 440.f);
    rseChannelGain(ctx, 1, 0.3f);
    Sleep(20000);
    rseDestroyContext(ctx);
    return 0;
}
