#include "stdafx.h"
#include "Scene_Splatting.h"
#include "./Objects/QuadObject.h"
#include "./Components/Transform.h"
#include "./Render/Shader.h"
#include "./Components/BoxCollider.h"
#include "./Utilities//Intersect.h"

#include "./System/Mouse.h"
Scene_Splatting::Scene_Splatting()
{
}


Scene_Splatting::~Scene_Splatting()
{
}

void Scene_Splatting::Init()
{
	bDelete = false;

	obj = new QuadObject;
	trans = obj->GetComponent<Transform>();
	//transform
	Transform* trans = obj->GetComponent<Transform>();
	trans->SetWorldPosition(desc.Width / 2, desc.Height / 2);
	//trnasform

	//shader
	{
		shader = new Shader(L"./Shader/Splatting.hlsl");
		obj->SetShader(shader);
	}
	//shader

	TexMetadata* meta;
	ScratchImage image;
	//Texutre
	{
		alphaTex = new Texture(L"_Textures/alpha01.dds");
		baseTexA = new Texture(L"_Textures/dirt01.dds");
		baseTexB = new Texture(L"_Textures/stone01.dds");
		
	}
	//Texture
	BoxCollider* collider = new BoxCollider(obj);
	collider->Scale(1.1f, 1.1f);
	obj->AddComponent(collider);
}

void Scene_Splatting::Release()
{
	SAFE_DELETE(obj);
}

void Scene_Splatting::Update()
{
	//if (Intersect::ObbCollision())
	//{

	//}
	if (Mouse::Get()->Up(2))
	{
		Scenes::Get()->SceneChange(L"Scene_2");
	}
	obj->Update();
}

void Scene_Splatting::PreRender()
{
}

void Scene_Splatting::Render()
{
	//D2D::GetDC()->PSGetShaderResources(0, 1, alphaTex);
	//D2D::GetDC()->PSGetShaderResources(1, 2, baseTex);

	//-------------------------------------------------------
	ID3D11ShaderResourceView* alpha[2];
	alpha[0] = *alphaTex;
	alpha[1] = *alphaTex;

	ID3D11ShaderResourceView* base[2];
	base[0] = *baseTexA;
	base[1] = *baseTexB;



	D2D::GetDC()->PSSetShaderResources(0, 2, alpha);
	D2D::GetDC()->PSSetShaderResources(2, 2, base);

	trans->SetWorldPosition(desc.Width * 1 / 4, desc.Height/ 2);
	obj->Update();
	obj->Render();
	trans->SetWorldPosition(desc.Width * 3 / 4, desc.Height / 2);
	obj->Update();
	obj->Render();


	obj->Insfactor();
}
