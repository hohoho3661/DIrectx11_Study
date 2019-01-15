#pragma once //한번 인크루드 된 헤더는 읽지 않겠다. 

#include <Windows.h>
#include <assert.h> //확인용으로 사용되는 녀석 
#include <stdio.h>  //<iostream> c++,  c
#include <string>
#include <vector>
#include <map>

using namespace std;

//DirectX SDK
// x라고 붙어있는 해더는 추가 해더 편의성 위주 추가 
#include <d3d11.h>
#include <d3dX11.h>
#include <d3dX10.h>
#include <d3dX10math.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

//DirectX Tex
// 택스쳐를 호출하기 위해서 필요한 해더 파일 

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
	wstring AppName; //타이틀 
	HINSTANCE hInstance; // os버전
	HWND Handle; //창에 번호 정수형태
	float Width; //창의 너비 해상도 
	float Height; //창의 높이
	bool bFullScreen; //전체 혹은 창모드 
};
extern _D2DDesc desc;

//directx에서 만들어져있는 포인털를 해제 
#define SAFE_RELEASE(p) { if(p) {(p)->Release(); (p) = 0; }}
//내가 만든 클래스 변수 포인터 삭제시 
#define SAFE_DELETE(p) { if(p) {delete (p); (p) = 0; }}
#define SAFE_DELETE_ARRAY(p)  {if(p) {delete[] (p); (p) = 0;}}

//Difine 1줄인식 "\" -> 1줄로 인식이 가능하겠금 
//##-> 왼족글 오른쪽 녀석 합쳐주는 녀석
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
