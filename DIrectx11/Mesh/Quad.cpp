#include "stdafx.h"
#include "Quad.h"


Quad::Quad()
	:Mesh(L"Quad.fbx")
{
	VertexCount = 4;
	vertices = new VertexTexture[VertexCount]
	{
		{-50, -50, 0, 1},
		{-50,  50, 0, 0},
		{ 50,  50, 1, 0},
		{ 50, -50, 1, 1},
	};
	//{
	//	VertexTexture(-50, -50, 0, 1),
	//	VertexTexture(-50,  50, 0, 0),
	//	VertexTexture( 50,  50, 1, 0),
	//	VertexTexture( 50, -50, 1, 1),
	//};
	//vertices[0] = VertexTexture(-50, -50, 0, 1);
	//vertices[1] = VertexTexture(-50,  50, 0, 0);
	//vertices[2] = VertexTexture( 50,  50, 1, 0);
	//vertices[3] = VertexTexture( 50, -50, 1, 1);

	IndexCount = 6;
	Indices = new UINT[IndexCount]{ 0,1,2,0,2,3 };

	CreateVertexBuffer(vertices, sizeof(VertexTexture));
	CreateIndexBuffer();
}


Quad::~Quad()
{
	SAFE_DELETE_ARRAY(vertices);
}

void Quad::Update()
{
	__super::Update(); //¹Ù·Î À­ ºÎ¸ð 
}

void Quad::Render()
{
	__super::Render();
}

void Quad::GetVertices(D3DXVECTOR3 * Position)
{
	for (int i = 0; i < VertexCount; i++)
	{
		Position[i] = vertices[i].Position;
	}
}
