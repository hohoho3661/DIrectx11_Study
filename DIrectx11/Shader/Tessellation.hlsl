
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

////////////////////////////////////////////////////////////////////

