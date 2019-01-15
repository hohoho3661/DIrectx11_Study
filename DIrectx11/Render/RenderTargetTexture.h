#pragma once
class RenderTargetTexture
{
public:
	void Clear(D3DXCOLOR color); //ȭ�� ����� + ���� ���ʹ� �ؽ��Ŀ� �׸��ڴ�.
	void SaveTexture(wstring file); //���Ϸ� ���� 
	ID3D11ShaderResourceView* Texture(); // ȣ�� 

	RenderTargetTexture();
	~RenderTargetTexture();

private:
	ID3D11RenderTargetView* RTV; //1. ���� 
	ID3D11Texture2D* Tex2D; //2.��ȯ(�̹��� �����)
	ID3D11ShaderResourceView* SRV; //3. ���(���̴��� �������� ������)
};
