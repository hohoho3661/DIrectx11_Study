#pragma once
class Camera
{
public:
	Camera();
	~Camera();

	void Render();

	void View(D3DXMATRIX* mat);
	void Ortho(D3DXMATRIX* mat);

	void SetRTT(ID3D11ShaderResourceView** srv);
	void Target();
private:
	//������ ������ ���� 
	struct ViewOrthoDesc
	{
		D3DXMATRIX View;
		D3DXMATRIX Ortho;
	}Data;

	ID3D11Buffer* buffer;

	//RenderTargetView
	class RenderTargetTexture* RTT;
};


