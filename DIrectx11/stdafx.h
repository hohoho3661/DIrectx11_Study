#pragma once //�ѹ� ��ũ��� �� ����� ���� �ʰڴ�. 

#include <Windows.h>
#include <assert.h> //Ȯ�ο����� ���Ǵ� �༮ 
#include <stdio.h>  //<iostream> c++,  c
#include <string>
#include <vector>
#include <map>

using namespace std;

//DirectX SDK
// x��� �پ��ִ� �ش��� �߰� �ش� ���Ǽ� ���� �߰� 
#include <d3d11.h>
#include <d3dX11.h>
#include <d3dX10.h>
#include <d3dX10math.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

//DirectX Tex
// �ý��ĸ� ȣ���ϱ� ���ؼ� �ʿ��� �ش� ���� 

#include <DirectXTex.h>
#pragma comment(lib, "DirectXTex.lib")
using namespace DirectX;

//ImGui
#include<imgui.h>
#include<imguiDx11.h>
#pragma comment (lib, "ImGui.lib")

//Systems
#include "./System/D2D.h"

//Utilities
#include "./Utilities/Defines.h"
#include "./Utilities/Vertex.h"
//Render
#include "./Render/Buffers.h"
#include "./Render/Texture.h"


struct _D2DDesc
{
	wstring AppName; //Ÿ��Ʋ 
	HINSTANCE hInstance; // os����
	HWND Handle; //â�� ��ȣ ��������
	float Width; //â�� �ʺ� �ػ� 
	float Height; //â�� ����
	bool bFullScreen; //��ü Ȥ�� â��� 
};
extern _D2DDesc desc;

//directx���� ��������ִ� �����и� ���� 
#define SAFE_RELEASE(p) { if(p) {(p)->Release(); (p) = 0; }}
//���� ���� Ŭ���� ���� ������ ������ 
#define SAFE_DELETE(p) { if(p) {delete (p); (p) = 0; }}
#define SAFE_DELETE_ARRAY(p)  {if(p) {delete[] (p); (p) = 0;}}

//Difine 1���ν� "\" -> 1�ٷ� �ν��� �����ϰڱ� 
//##-> ������ ������ �༮ �����ִ� �༮
//Get##Name-> Name = Position -> GetPosition
//#define GetSet(Type, Name, Param) \
//	Type Get##Name()\
//	{\
//		return Param;\
//	}\
//	void Set##Name(Type _param)\
//	{\
//		Param = _param;\
//	}
