#pragma once

class Shader
{
public:
	Shader(wstring file);
	~Shader();

	void Render();

private:

	ID3D11SamplerState* SamplerState;

	ID3D11InputLayout* layout;

	ID3D10Blob* vsBlob;
	ID3D10Blob* psBlob;
	ID3D11VertexShader* vs;
	ID3D11PixelShader* ps;

	void CreateShader(wstring file);
	void CreateSamplerState();

	void ErrorMessage(ID3D10Blob* error, HRESULT hr);

};

class Materials
{
public:
	static Shader* Load(wstring file);
	static void Deleate();
private:
	friend class Shader;

	static map<wstring, Shader*> mapShader;
};