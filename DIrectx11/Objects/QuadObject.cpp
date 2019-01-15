#include "stdafx.h"
#include "QuadObject.h"
#include "./Mesh/Quad.h"
#include "./Render/Shader.h"
#include "./Components//BoxCollider.h"
QuadObject::QuadObject()
{
	mesh = Meshes::Load<Quad>();
	shader = Materials::Load(L"./Shader/TextureMapping.hlsl");

	BoxCollider* collider = new BoxCollider(this);
	Components.push_back(collider);
}


QuadObject::~QuadObject()
{
}
