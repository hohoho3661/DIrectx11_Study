#include "stdafx.h"
#include "Vertex.h"

#define XY DXGI_FORMAT_R32G32_FLOAT
#define XYZ DXGI_FORMAT_R32G32B32_FLOAT
#define APEENDALIGNED D3D11_APPEND_ALIGNED_ELEMENT
#define VERTEX D3D11_INPUT_PER_VERTEX_DATA

D3D11_INPUT_ELEMENT_DESC Vertex::desc[] = 
{
	{"POSITION", 0, XYZ, 0, 0, VERTEX, 0}
};
UINT Vertex::count = ARRAYSIZE(desc);

D3D11_INPUT_ELEMENT_DESC VertexTexture::desc[] = 
{
	{"POSITION", 0, XYZ, 0, 0, VERTEX, 0},
	{"UV", 0, XY, 0, APEENDALIGNED, VERTEX, 0}
};
UINT VertexTexture::count = ARRAYSIZE(desc);
