
//file Tessellation.hlsl

// vs- hs- ds- ps

struct VertexInput
{
    float4 Position : POSITION;
    float2 Uv : UV0;
};

struct HullInput
{
    float4 Position : POSITION;
    float2 Uv : UV0;
};

HullInput VS (VertexInput input)
{
    HullInput output;
    output.Position = input.Position;
    output.Uv = input.Uv;

    return output;
}

cbuffer HS_Amount
{
    float4 Amount; // 버텍스를 몇개로 자를 것인가?
    float3 Padding;
};

struct ConstantOutPut
{
    float edges[3] : SV_TessFactor; // 모서리
    float inside : SV_InsideTessFactor; // 삼각형값
};

struct DomainInput
{
    float4 Position : POSITION;
    float2 Uv : UV0;
};

ConstantOutPut Constant(InputPatch<HullInput, 3> inputPath, uint patchid : SV_PrimitiveID) // HullInput 3개가 들어가고,,, 잘라줌
{
    ConstantOutPut output;
    output.edges[0] = Amount;
    output.edges[1] = Amount;
    output.edges[2] = Amount;

    output.inside = Amount;

    return output;
}

///////////////////////////////////////////////
//      HULL Shader
///////////////////////////////////////////////

[domain("tri")] // 생성할 도형형 tri, quad
[partitioning("integer")]
[outputtopology("triangle_cw")]
[outputcontrolpoints(3)] // controlpoints = 꼭지점
[patchconstantfunc("Constant")]

DomainInput HS(InputPatch<HullInput, 3> patch, uint pointId : SV_OutputControlPointID,
                uint patchID : SV_PrimitiveID)
{
    DomainInput output;

    output.Position = patch[pointId].Position;
    output.Uv = patch[pointId].Uv;

    return output;
}

///////////////////////////////////////////////
//      Domain Shader
///////////////////////////////////////////////

cbuffer DS_ViewOrtho : register(b0)
{
    matrix View;
    matrix Projection;
}

cbuffer DS_World : register(b1)
{
    matrix World;
}

struct PixelInput
{
    float4 Position : SV_Position;
    float2 Uv : UV0;
};

[domain("tri")]
PixelInput DS (ConstantOutPut input, float3 uvwCoord : SV_DomainLocation,
                const OutputPatch<DomainInput, 3> patch)
{
    PixelInput output;

    float4 vertexPosition;
    vertexPosition = uvwCoord.x * patch[0].Position 
                    + uvwCoord.y * patch[1].Position 
                    + uvwCoord.z * patch[2].Position;

    output.Position = mul(vertexPosition, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);

    output.Uv = uvwCoord.x * patch[0].Uv
               + uvwCoord.y * patch[1].Uv;

    return output;
}

///////////////////////////////////////////////
//      Pixel Shader
///////////////////////////////////////////////

Texture2D DiffuseMap;
SamplerState Sampler;

float4 PS(PixelInput input) : SV_Target
{
    return DiffuseMap.Sample(Sampler, input.Uv);
}