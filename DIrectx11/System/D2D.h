#pragma once
class D2D
{
private:
	//장치 생성시 필요한 변수 
	static ID3D11Device* device; 
	//랜더링에 필요한 변수 
	static ID3D11DeviceContext* deviceContext;

	IDXGISwapChain* swapChain;

	ID3D11RenderTargetView* RTV; //전방버퍼 

	D2D();
	~D2D();

	static D2D* instance;
public:
	static D2D* Get();
	static void Delete();

	static ID3D11Device* GetDevice() { return device; }
	static ID3D11DeviceContext* GetDC() { return deviceContext; }


	//Device, DeviceContext, SwapChain 
	void CreateDeviceAndSwapChain();
	//BackBuffer
	void CreateBackBuffer();
	//viewport(창크기)
	void CreateViewport();
	//후면버퍼 내용삭제 
	void Clear(D3DXCOLOR color);
	//후면 버퍼 내용 -> 전방버퍼 
	void Present();
};
	

