#pragma once
class RenderTargetTexture
{
public:
	void Clear(D3DXCOLOR color); //화면 지우기 + 이후 부터는 텍스쳐에 그리겠다.
	void SaveTexture(wstring file); //파일로 저장 
	ID3D11ShaderResourceView* Texture(); // 호출 

	RenderTargetTexture();
	~RenderTargetTexture();

private:
	ID3D11RenderTargetView* RTV; //1. 저장 
	ID3D11Texture2D* Tex2D; //2.변환(이미지 저장용)
	ID3D11ShaderResourceView* SRV; //3. 출력(셰이더로 보내지는 데이터)
};
