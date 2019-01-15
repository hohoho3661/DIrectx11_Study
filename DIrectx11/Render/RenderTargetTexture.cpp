#include "stdafx.h"
#include "RenderTargetTexture.h"

void RenderTargetTexture::Clear(D3DXCOLOR color)
{
	D2D::Get()->GetDC()->OMSetRenderTargets(1, &RTV, NULL);
	D2D::Get()->GetDC()->ClearRenderTargetView(RTV, color);
}

void RenderTargetTexture::SaveTexture(wstring file)
{
	HRESULT hr;
	hr = D3DX11SaveTextureToFile
	(
		D2D::Get()->GetDC(),
		Tex2D,
		D3DX11_IFF_PNG,
		file.c_str()
	);
	assert(SUCCEEDED(hr));
}

ID3D11ShaderResourceView * RenderTargetTexture::Texture()
{
	return SRV;
}

RenderTargetTexture::RenderTargetTexture()
{
	D3D11_TEXTURE2D_DESC texDesc;
	ZeroMemory(&texDesc, sizeof(D3D11_TEXTURE2D_DESC));

	texDesc.Width = desc.Width;
	texDesc.Height = desc.Height;
	texDesc.MipLevels = 1;
	texDesc.ArraySize = 1;
	//Texture(원본), 출력(영역), 사이즈가 다를 경우 
	texDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	texDesc.CPUAccessFlags = 0;
	texDesc.MiscFlags = 0;
	//float4 -> RGBA 
	//DWORD  -> ARGB
	//Texture-> ABGR
	HRESULT hr = D2D::Get()->GetDevice()->CreateTexture2D
	(
		&texDesc, NULL, &Tex2D
	);

	D3D11_RENDER_TARGET_VIEW_DESC RTVDesc;
	ZeroMemory(&RTVDesc, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
	RTVDesc.Format = texDesc.Format;
	RTVDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	RTVDesc.Texture2D.MipSlice = 0;

	D2D::Get()->GetDevice()->CreateRenderTargetView
	(
		Tex2D, &RTVDesc, &RTV
	);
	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
	ZeroMemory(&SRVDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	SRVDesc.Format = texDesc.Format;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MipLevels = 1;
	SRVDesc.Texture2D.MostDetailedMip = 0;

	D2D::GetDevice()->CreateShaderResourceView
	(
		Tex2D,&SRVDesc, &SRV
	);
}


RenderTargetTexture::~RenderTargetTexture()
{
	SAFE_RELEASE(Tex2D);
	SAFE_RELEASE(RTV);
	SAFE_RELEASE(SRV);
}
