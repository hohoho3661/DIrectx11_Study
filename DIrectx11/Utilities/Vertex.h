#pragma once

struct Vertex
{
	D3DXVECTOR3 Position;
	Vertex()
	{
		Position = { 0.0f,0.0f,0.0f };
	}
	Vertex(float x, float y)
	{
		Position = { x, y, 0.0f };
	}
	Vertex(D3DXVECTOR2 vec)
	{
		Position = { vec.x, vec.y, 0.0f };
	}

	static D3D11_INPUT_ELEMENT_DESC desc[];
	static UINT count;
};

//Texture Mapping
struct VertexTexture
{
	D3DXVECTOR3 Position;
	D3DXVECTOR2 Uv; //이미지 좌표 

	VertexTexture()
	{
		Position = { 0.0f,0.0f,0.0f };
		Uv = { 0.0f,0.0f };
	}
	VertexTexture(float x, float y, float u, float v)
	{
		Position = { x, y, 0.0f };
		Uv = { u, v };
	}

	static D3D11_INPUT_ELEMENT_DESC desc[];
	static UINT count;
};