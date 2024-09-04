#include "PostProcess.hlsli"

struct PixelShaderOutput
{
    float32_t4 color : SV_TARGET0;
	
};

Texture2D<float32_t4> gTexture : register(t0);

SamplerState gSampler : register(s0);

struct Random
{
    float32_t time;
};

ConstantBuffer<Random> gRandom : register(b0);

float32_t rand2dTo1d(float32_t2 value, float32_t2 dotDir = float32_t2(12.9898, 78.233))
{
    float32_t2 smallValue = sin(value);
    float32_t random = dot(smallValue, dotDir);
    random = frac(sin(random) * 143758.5453);
    return random;
}

PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    
    float32_t random = rand2dTo1d(input.texcoord * gRandom.time);
    output.color = float32_t4(random, random, random, 1.0f);
    return output;
};