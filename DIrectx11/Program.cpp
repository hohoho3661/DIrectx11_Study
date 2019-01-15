#include "stdafx.h"
#include "Program.h"
#include "./Scenes/Scene.h"
#include "./Test/SceneChangeTest.h"
#include "./Scenes/Scene_Splatting.h"
#include "./System/Mouse.h"
Program::Program()
{
	bShowDemo = false;
	bShowInfo = false;
	bShowInsfactor = true;
}


Program::~Program()
{
}

void Program::Init()
{
	
	mainCamera = new Camera;
	
	//NowScene = new Scene_Splatting;
	//NowScene->Init();
	Scenes::Get()->AddScene(L"Scene_1", new Scene_Splatting());
	Scenes::Get()->AddScene(L"Scene_2", new SceneChangeTest());

	Scenes::Get()->SceneChange(L"Scene_1");

	CreateBlendState();
}

void Program::Release()
{
	SAFE_DELETE(mainCamera);
	//Scenes::Delete();
	Mouse::Get()->Delete();
	//SAFE_DELETE(NowScene);
}

void Program::Update()
{
	Mouse::Get()->Update();
	Scenes::Get()->Update();
	//NowScene->Update();

	//D3DXVECTOR2 vPos = { 350.f, 250.f };
	//D3DXVECTOR2 vPos = {desc.Width, desc.Height};

	//D3DXMATRIX world;
	//D3DXMatrixIdentity(&world);

	//world._41 = desc.Width / 2;
	//world._42 = desc.Height / 2;
	//D3DXMATRIX ortho;

	//mainCamera->Ortho(&ortho);

	//D3DXMATRIX view;
	//mainCamera->View(&view);
	//D3DXVec2TransformCoord(&vPos, &vPos, &world);
	//D3DXMatrixTranspose(&view, &view);
	//D3DXVec2TransformCoord(&vPos, &vPos, &view);
	//D3DXMatrixTranspose(&ortho, &ortho);
	//D3DXVec2TransformCoord(&vPos, &vPos, &ortho);

	//int a = 0;

	// 화면의 좌표는 -1 ~ 1 (로컬 * 월드 * 뷰 * 프로젝션 )
	// 마우스의 좌표 -1 ~ 1 프로젝션^-1 * 뷰 ^-1  
}

void Program::PreRender()
{
	Scenes::Get()->PreRender();

}

void Program::Render()
{
	mainCamera->Render();
	//NowScene->Render();
	Scenes::Get()->Render();

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("Windows"))
		{
			ImGui::MenuItem("Info", "Ctrl + F1", &bShowInfo);
				
			ImGui::MenuItem("Demo", "Ctrl + F2", &bShowDemo);

			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}
	ShowInfo();
	ShowDemo();
	
}


void Program::CreateBlendState()
{
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));

	blendDesc.RenderTarget[0].BlendEnable = false;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	D2D::Get()->GetDevice()->CreateBlendState(&blendDesc, &blendState[0]);

	//src Color = Color blendOp src Alpha

	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA; //띄울 도형에 대한 색상에 계산한 값
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA; //그자리에 그려져있는 픽섹 색상 에 계산할 값 
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	D2D::Get()->GetDevice()->CreateBlendState(&blendDesc, &blendState[1]);

}

void Program::ShowInfo()
{

	if (bShowInfo)
	{
		ImGui::Begin("Info",&bShowInfo);
		{
			ImGui::LabelText("", "FPS : %0.2f", ImGui::GetIO().Framerate);
		}
		ImGui::End();
	}
}

void Program::ShowDemo()
{
	if (bShowDemo)
	{
		ImGui::ShowDemoWindow();
	}
}

void Program::ShowInsfactor()
{
	ImGui::Begin(WS_INSFACTOR, &bShowInsfactor, ImGuiWindowFlags_AlwaysAutoResize);

	ImGui::End();
}
