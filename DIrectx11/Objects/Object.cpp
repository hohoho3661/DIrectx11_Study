#include "stdafx.h"
#include "Object.h"

#include "./Components/Transform.h"
#include "./Mesh/Mesh.h"
#include "./Render/Shader.h"

Object::Object()
	:mesh(NULL),shader(NULL)
{
	Components.push_back(new Transform);
	bActive = true;
}


Object::~Object()
{
	for (Component* comp : Components)
		SAFE_DELETE(comp);
}

void Object::Update()
{
	if (bActive)
	{
		for (Component* comp : Components)
			comp->EnableUpdate();
		if(mesh != NULL) mesh->Update();
	}
}

void Object::Render()
{
	if (bActive)
	{
		Components[0]->EnableRender();

		if (mesh != NULL) mesh->Render();

		//for (Component* comp : Components)
		//	comp->EnableRender();
		for (int i = 1; i < Components.size(); i++)
		{
			Components[i]->EnableRender();
		}

		if (shader != NULL) shader->Render();
	}
	Insfactor();
}

void Object::Insfactor()
{
	for (Component* comp : Components)
		comp->ShowInspactor();
}

void Object::AddComponent(Component * comp)
{
	Components.push_back(comp);
}

void Object::SetShader(Shader * shader)
{
	if (this->shader == shader) return;

	this->shader = shader;
}
