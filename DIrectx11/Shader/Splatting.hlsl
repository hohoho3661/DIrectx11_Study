// Splatting.hlsl

// 2d 작업할때 사용 
cbuffer VS_ViewOrtho
{
    matrix View;
    matrix Projection;
};

cbuffer VS_World
{
    matrix World;
};

struct VertexInput
{
    float4 position : POSITION;
    float2 Uv : UV0;
};

struct PixelInput
{
    float4 position : SV_POSITION;
    float2 Uv : UV0;
};

PixelInput VS(VertexInput input)
{
    PixelInput output;

    output.position = mul(input.position, World);
    output.position = mul(output.position, View);
    output.position = mul(output.position, Projection);

    output.Uv = input.Uv;

    return output;
}

Texture2D AlphaTex[2] : register(t0);
Texture2D BaseTex[2] : register(t2);
SamplerState Sampler : register(s0);

//shader 0.0~ 1.0f

float4 PS(PixelInput input) : SV_TARGET
{
    float4 AlphaColor1 = AlphaTex[0].Sample(Sampler, input.Uv);
    float4 AlphaColor2 = AlphaTex[1].Sample(Sampler, input.Uv);

    float4 BaseColor1 = BaseTex[0].Sample(Sampler, input.Uv);
    float4 BaseColor2 = BaseTex[1].Sample(Sampler, input.Uv);

    float factor1 = (AlphaColor1.x + AlphaColor1.y + AlphaColor1.z) / 3;
    float factor2 = (AlphaColor2.x + AlphaColor2.y + AlphaColor2.z) / 3;

    factor1 = saturate(factor1); //0~1 
    factor2 = saturate(1 - factor2); //0~1 

    return BaseColor1 * factor1 + BaseColor2 * factor2;
}
