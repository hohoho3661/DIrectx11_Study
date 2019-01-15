#include "stdafx.h"
#include "Gizmo.h"
#include "./Render/Shader.h"

Line::Line(D3DXVECTOR3 start, D3DXVECTOR3 end)
{
	shader = Materials::Load(L"./Shader/Effect.hlsl");

	worldBuffer = new WorldDesc;
	colorBuffer = new ColorDesc;
	VertexTexture* vertices = new VertexTexture[2];
	vertices[0].Position = start;
	vertices[1].Position = end;

	D3D11_BUFFER_DESC bufferDesc = { 0 };
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.ByteWidth = sizeof(VertexTexture) * 2;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA subResource;
	subResource.pSysMem = vertices;

	D2D::GetDevice()->CreateBuffer(&bufferDesc, &subResource, &vertexBuffer);

	SAFE_DELETE_ARRAY(vertices);
}

Line::~Line()
{
	SAFE_DELETE(shader);
	SAFE_DELETE(worldBuffer);
	SAFE_DELETE(colorBuffer);
	SAFE_RELEASE(vertexBuffer);
}

void Line::Update()
{
}

void Line::Render()
{
	// 픽셀 쉐이더면 픽셀 쉐이더, 버텍스 쉐이더면 버텍스 쉐이더 한데 각각 하나씩 보내줘야 한다. 

	// 버택스 어디서부터 읽어라 
	UINT offset = 0;
	UINT stride = sizeof(VertexTexture);	// ~까지 읽는다. 


	colorBuffer->SetPSBuffer(0);
	worldBuffer->SetVSBuffer(1);

	shader->Render();

	D2D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D2D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);// 어떤 도형을 그릴 것인가??
	D2D::GetDC()->Draw(2, 0);
}

void Line::World(D3DXMATRIX world)
{
	worldBuffer->Set(world);
}
