
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
    float4 Amount; // ���ؽ��� ��� �ڸ� ���ΰ�?
    float3 Padding;
};

struct ConstantOutPut
{
    float edges[3] : SV_TessFactor; // �𼭸�
    float inside : SV_InsideTessFactor; // �ﰢ����
};

struct DomainInput
{
    float4 Position : POSITION;
    float2 Uv : UV0;
};

ConstantOutPut Constant(InputPatch<HullInput, 3> inputPath, uint patchid : SV_PrimitiveID) // HullInput 3���� ����,,, �߶���
{
    ConstantOutPut output;
    output.edges[0] = Amount;
    output.edges[1] = Amount;
    output.edges[2] = Amount;

    output.inside = Amount;

    return output;
}

////////////////////////////////////////////////////////////////////

