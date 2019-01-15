#pragma once
class D2D
{
private:
	//��ġ ������ �ʿ��� ���� 
	static ID3D11Device* device; 
	//�������� �ʿ��� ���� 
	static ID3D11DeviceContext* deviceContext;

	IDXGISwapChain* swapChain;

	ID3D11RenderTargetView* RTV; //������� 

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
	//viewport(âũ��)
	void CreateViewport();
	//�ĸ���� ������� 
	void Clear(D3DXCOLOR color);
	//�ĸ� ���� ���� -> ������� 
	void Present();
};
	

