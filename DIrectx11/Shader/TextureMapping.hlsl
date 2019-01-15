//TextureMapping.hlsl

cbuffer VS_ViewOrtho : register(b0)
{
    matrix View;
    matrix Projection;
}

cbuffer VS_World : register(b1)
{
    matrix World;
}

struct VertexInput
{
    float4 Position : POSITION;
    float2 Uv : UV;
};

struct PixelInput
{
    float4 Position : SV_POSITION;
    float2 Uv : UV;
};

PixelInput VS (VertexInput input)
{
    PixelInput output;

    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);

    output.Uv = input.Uv;

    return output;
}

Texture2D DiffuseTex : register(t0);
SamplerState Sampler : register(s0);

float4 PS(PixelInput input) : SV_TARGET
{
    return DiffuseTex.Sample(Sampler, input.Uv);
}