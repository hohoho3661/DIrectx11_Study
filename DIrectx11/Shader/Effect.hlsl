//HLSL 
cbuffer VS_ViewOrtho : register(b0)
{
    matrix View;
    matrix Ortho; //Projection
}
cbuffer VS_World : register(b1)
{
    matrix World;
}

cbuffer PS_Color : register(b0)
{
    float4 color;
}
struct VertexInput
{
	float4 position : POSITION;
    float2 Uv : UV0;
};
struct PixelInput
{
	float4 position : SV_POSITION;
};
PixelInput VS(VertexInput input)
{
	PixelInput output;
    output.position = mul(input.position, World);
    output.position = mul(output.position, View);
    output.position = mul(output.position, Ortho);

	return output;
}
float4 PS(PixelInput input) : SV_TARGET
{
	return color;
}

