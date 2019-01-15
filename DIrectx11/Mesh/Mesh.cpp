#include "stdafx.h"
#include "Mesh.h"

map<wstring, Mesh*> Meshes::meshes;

Mesh::Mesh(wstring file)
{
	Meshes::meshes[file] = this;
}


Mesh::~Mesh()
{
	SAFE_RELEASE(VertexBuffer);
	SAFE_RELEASE(IndexBuffer);
	SAFE_DELETE_ARRAY(Indices);
}

void Mesh::Update()
{
}

void Mesh::Render()
{
	UINT offset = 0;
	D2D::Get()->GetDC()->IASetVertexBuffers(0, 1, &VertexBuffer, &strid, &offset);
	D2D::Get()->GetDC()->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	D2D::Get()->GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	D2D::Get()->GetDC()->DrawIndexed(IndexCount, 0, 0);
}

void Mesh::CreateVertexBuffer(void * Data, UINT size)
{
	this->Data = Data;
	this->strid = size;

	D3D11_BUFFER_DESC bufferDesc = { 0 };
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.ByteWidth = size * VertexCount;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA data = { 0 };
	data.pSysMem = Data;

	HRESULT hr = D2D::Get()->GetDevice()->CreateBuffer(&bufferDesc, &data, &VertexBuffer);
	assert(SUCCEEDED(hr));
}

void Mesh::CreateIndexBuffer()
{
	D3D11_BUFFER_DESC bufferDesc = { 0 };
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER; //VERTEX -> INDEX 수정
	bufferDesc.ByteWidth = sizeof(UINT) * IndexCount; //size * VertexCount -> sizeof(UINT) * IndexCount 수정
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA data = { 0 };
	data.pSysMem = Indices;

	D2D::Get()->GetDevice()->CreateBuffer(&bufferDesc, &data, &IndexBuffer); //VertexBuffer -> IndexBuffer 수정
}

void Mesh::CopyVertices(void* vertices, UINT* count)
{
	vertices = Data;
	*count = VertexCount;
}
