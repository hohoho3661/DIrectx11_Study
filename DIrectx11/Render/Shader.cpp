#include "stdafx.h"
#include "./Shader.h"

Shader::Shader(wstring file)
{
	CreateShader(file);
	CreateSamplerState();
}

Shader::~Shader()
{
	SAFE_RELEASE(vsBlob);
	SAFE_RELEASE(psBlob);
	SAFE_RELEASE(vs);
	SAFE_RELEASE(ps);
	SAFE_RELEASE(layout);
	SAFE_RELEASE(SamplerState);
}

void Shader::Render()
{
	D2D::Get()->GetDC()->VSSetShader(vs, 0, 0);
	D2D::Get()->GetDC()->PSSetShader(ps, 0, 0);
	D2D::Get()->GetDC()->IASetInputLayout(layout);
	D2D::Get()->GetDC()->PSSetSamplers(0, 1, &SamplerState);
}

void Shader::CreateShader(wstring file)
{
	HRESULT hr;
	ID3D10Blob* error;
	// 
	D3DX11CompileFromFile(file.c_str(), NULL, NULL, "VS", "vs_5_0",
		0, 0, NULL, &vsBlob, &error, &hr);
	ErrorMessage(error, hr);

	D3DX11CompileFromFile(file.c_str(), NULL, NULL, "PS", "ps_5_0",
		0, 0, NULL, &psBlob, &error, &hr);
	ErrorMessage(error, hr);

	D2D::Get()->GetDevice()->CreateVertexShader(
		vsBlob->GetBufferPointer(),
		vsBlob->GetBufferSize(),
		NULL, &vs
	);
	D2D::Get()->GetDevice()->CreatePixelShader(
		psBlob->GetBufferPointer(),
		psBlob->GetBufferSize(),
		NULL, &ps
	);

	hr = D2D::Get()->GetDevice()->CreateInputLayout(
		VertexTexture::desc,
		VertexTexture::count,
		vsBlob->GetBufferPointer(),
		vsBlob->GetBufferSize(),
		&layout);
	assert(SUCCEEDED(hr));

}

void Shader::CreateSamplerState()
{

	D3D11_SAMPLER_DESC samplerDesc;

	ZeroMemory(&samplerDesc, sizeof(D3D11_SAMPLER_DESC));

	samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.BorderColor[0] = 1.0f;

	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = FLT_MAX;

	D2D::Get()->GetDevice()->CreateSamplerState(&samplerDesc, &SamplerState);
}

void Shader::ErrorMessage(ID3D10Blob * error, HRESULT hr)
{
	if (error != NULL)
	{
		MessageBoxA(NULL, (char*)error->GetBufferPointer(),
			"Shader Error", MB_OK);
		SAFE_RELEASE(error);
	}
	assert(SUCCEEDED(hr));
}
//-----------------------------------------------------------------------------------//
// Materials
//-----------------------------------------------------------------------------------//

map<wstring, Shader*> Materials::mapShader;

Shader * Materials::Load(wstring file)
{
	auto iter = mapShader.find(file);
	if (iter == mapShader.end())
	{
		Shader* temp = new Shader(file);
		return mapShader[file] = temp;
	}
	return  mapShader[file];
}

void Materials::Deleate()
{
	for (auto temp : mapShader)
	{
		SAFE_DELETE(temp.second);
	}
	mapShader.clear();
}
