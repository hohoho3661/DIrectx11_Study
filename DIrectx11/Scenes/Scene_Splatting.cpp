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

	D3D11_RASTERIZER_DESC rsDesc;
	ZeroMemory(&rsDesc, sizeof(D3D11_RASTERIZER_DESC)); // 초기화

	//ccw 카운트클락와치(역시계방향 지우겠다)     cw 클락와치(시계방향 지우겠다)
	rsDesc.CullMode = D3D11_CULL_NONE; // CullMode = 방향설정    ,,, NONE = 앞뒷면 다 출력,, 당연히 프레임은 깎임
	rsDesc.FillMode = D3D11_FILL_WIREFRAME; // SOLID = 기본,, WIREFRAME = 정점끼리 연결
	D2D::GetDevice()->CreateRasterizerState(&rsDesc, &raterizer);
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
	D2D::GetDC()->RSSetState(raterizer); // RS = 랜더스테이스 ,,,,  선으로만 출력
	

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
