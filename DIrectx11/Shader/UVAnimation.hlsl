//UVAnimation.hlsl

cbuffer VS_ViewOrtho : register(b0)
{
    matrix View;
    matrix Projection;
}
cbuffer VS_World : register(b1)
{
    matrix World;
}
cbuffer VS_Uv : register(b2)
{
    float2 Start;
    float2 End;
}
cbuffer VS_Size : register(b3)
{
    float2 Size;
}

struct VertexInput
{
    float4 Position : POSITION;
    float2 Uv : UV0;
};

struct PixelInput
{
    float4 Position : SV_POSITION;
    float2 Uv : UV0;
};

PixelInput VS(VertexInput input)
{
    PixelInput output;
    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);

    output.Uv.x = Start.x / Size.x + input.Uv.x * (End.x - Start.x) / Size.x;
    output.Uv.y = Start.y / Size.y + input.Uv.y * (End.y - Start.y) / Size.y;

    //output.Uv = input.Uv;
    return output;
}

SamplerState Sampler : register(s0);
Texture2D DiffuseTex : register(t0);

float4 PS(PixelInput input) : SV_TARGET
{
    return DiffuseTex.Sample(Sampler, input.Uv);
}
