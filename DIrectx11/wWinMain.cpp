#pragma once
#include "stdafx.h"
#include "./System/Window.h"
int WINAPI WinMain(
	HINSTANCE instance, //������ os
	HINSTANCE prevInstance, //������ ��� x 
	LPSTR param,
	int command
)
{
	D3DXVECTOR3 vector;
	D3DXMATRIX matrix;

	desc.AppName = L"D2D Game";
	desc.hInstance = instance;
	desc.bFullScreen = false;
	desc.Handle = NULL;
	desc.Width = 1280;
	desc.Height = 720;

	Window* window = new Window();
	WPARAM wParam = window->Run();
	delete window;

	return wParam;
}
