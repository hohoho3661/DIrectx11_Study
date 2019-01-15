#pragma once
#include "./Viewer/Camera.h"
class Program
{
public:
	Program();
	~Program();

	void Init();
	void Release();
	void Update();
	void PreRender(); 
	void Render();

private:
	bool bShowInfo;
	bool bShowDemo;
	bool bShowInsfactor;

	Camera * mainCamera;

	class Scene* NowScene;

private:
	ID3D11BlendState* blendState[2];//0 blend x 1 blend
	void CreateBlendState();
	void ShowInfo();
	void ShowDemo();
	void ShowInsfactor();// object의 components 확인및 수치 조정
};

