#include <windows.h>
#include <RSE/RSE.h>

int main(void)
{
    RseContext* ctx;

    ctx = rseCreateContext(48000, 16);
    rseChannelType(ctx, 0, RSE_WAVE_SAWTOOTH);
    rseChannelFrequency(ctx, 0, 440.f);
    rseChannelGain(ctx, 0, 0.4f);
    rseChannelFrequencyModulation(ctx, 0, 440.f * 0.1, 20.f, 1);
    Sleep(20000);
    rseDestroyContext(ctx);
    return 0;
}
