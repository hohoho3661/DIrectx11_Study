#include "stdafx.h"
#include "Window.h"
#include "./Render/Shader.h"
#include "./Mesh/Mesh.h"
_D2DDesc desc;

LRESULT CALLBACK Window::WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui::WndProc(handle, message, wParam, lParam)) return true;

	if (message == WM_CLOSE || message == WM_DESTROY)
	{
		PostQuitMessage(0);

		return 0;
	}

	return DefWindowProc(handle,message,wParam,lParam);
}

Window::Window()
{
	//window ��� 
	WNDCLASSEX wndClass; //������ ����ü 
	wndClass.cbClsExtra = 0; //�޸� �׳� 0
	wndClass.cbWndExtra = 0; //�޸� �׳� 0
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); //â�� ������ ���
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hInstance = desc.hInstance;
	wndClass.lpszClassName = desc.AppName.c_str();
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	//2byte 
	WORD wHr = RegisterClassEx(&wndClass);

	//assert(����)// ������ ���� ���� �ڵ���� 
	//��� ���Ͽ��� ���° ��, ������ �������� 
	assert(wHr != 0 && "Not RegisterClass");

	desc.Handle = CreateWindowEx
	(
		WS_EX_APPWINDOW,
		desc.AppName.c_str(), // Ŭ���� �̸�(��ϵ� Ŭ���� �̸��� ������ ���ƾ� ��)
		desc.AppName.c_str(), // Ÿ��Ʋ �̸�,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, // â�� ������ġ ���� 100
		CW_USEDEFAULT, // â�� ���� ���� ��ġ 100
		CW_USEDEFAULT, // â�� ���� ũ�� 1280
		CW_USEDEFAULT, // â�� ���� ũ�� 768
		NULL,			//�θ� ������ 
		(HMENU)NULL,	//�޴�
		desc.hInstance,	
		NULL			//�Ⱦ��� �༮ 
	);

	assert(desc.Handle != NULL && "Not CreateWindow");
	RECT rc = 
	{ 0,0,(LONG)desc.Width,(LONG)desc.Height };

	UINT centerX = (GetSystemMetrics(SM_CXSCREEN) - (UINT)desc.Width) / 2;
	UINT centerY = (GetSystemMetrics(SM_CYSCREEN) - (UINT)desc.Height) / 2;
	//âũ�� �缳��
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	//â�̵�
	MoveWindow(
		desc.Handle,
		centerX, centerY,
		rc.right - rc.left,
		rc.bottom - rc.top,
		TRUE
	);
	//â���� 
	ShowWindow(desc.Handle, SW_SHOWNORMAL);
	SetForegroundWindow(desc.Handle);
	SetFocus(desc.Handle);
}


Window::~Window()
{
	DestroyWindow(desc.Handle);

	UnregisterClass(desc.AppName.c_str(),
		desc.hInstance);
}

WPARAM Window::Run()
{
	MSG msg = { 0 };

	game = new Program;
	game->Init();

	//���ӿ� �޼��� ���� 
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			game->Update();
			ImGui::Update();


			game->PreRender();

			D2D::Get()->Clear(0xff808080);
			{
				game->Render();
				ImGui::Render();
			}
			D2D::Get()->Present();
		}
	}

	Meshes::Delete();
	Materials::Deleate();
	Textures::Delete();
	
	game->Release();
	SAFE_DELETE(game);

	return msg.wParam;
}
