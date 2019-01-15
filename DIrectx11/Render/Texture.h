#pragma once

//  �̱���(���̳���) 
//struct TextureInfo
//{
//	ID3D11ShaderResourceView* SRV;
//	D3DX11_IMAGE_INFO Info;
//};
// SRV-> ���̴����� ������ ������ 
// Texture2D-> �̹��� ������ 

class Texture // �̹��� ����
{
private:
	wstring file;
	TexMetadata metaData; // �ؽ��� ���� (���� ���� ) DirextXTex�� �� �� �ִ� �ش� �Ӽ� (��ȯ)
	ID3D11ShaderResourceView* view;

public:
	// Load �ؽ��İ� ������ �ִ� private ~ public ���� public ���� ��� ����
	friend class Textures;
	//
public:
	Texture(wstring file, D3DX11_IMAGE_LOAD_INFO* loadinfo = NULL);
	~Texture();

public:
	static void SaveFile(wstring file, ID3D11Texture2D* src);
	//DXGI_FORMAT : ũ�⿡ ���� �̹��� ������ �޶�����. 
	// ID3D11Texture* �����Ͱ� ����. (I : ���������Լ��� �Ǿ� �ְ�,  Iterator Ÿ�� )  ���������Լ��� 1���� ���� ��� new�� �ȵȴ�. 
	static D3D11_TEXTURE2D_DESC ReadPixels(
		IN ID3D11Texture2D* src, IN DXGI_FORMAT readFormat, OUT std::vector<D3DXCOLOR>* pixels);

public:
	void GetImageInfo(TexMetadata* data)
	{
		*data = metaData;
	}
public:
	void SaveFile(wstring file);public:
	D3D11_TEXTURE2D_DESC ReadPixels(DXGI_FORMAT readFormat, std::vector<D3DXCOLOR>* pixels);
	operator ID3D11ShaderResourceView* () { return  view; }		// ex) Texture* temp; temp(); -> view return ; // ������ �ʴ� �ּҰ� 
	ID3D11ShaderResourceView*const* GetView() { return &view; }
	wstring GetFile() { return file; }
	UINT GetWidth() { return metaData.width; }
	UINT GetHeight() { return metaData.height; }
	
	
};

struct TextureDesc
{
	wstring file;
	UINT width, height;
	TexMetadata metaData;
	ID3D11ShaderResourceView* view;

	bool operator== (const TextureDesc& desc)
	{
		// A += B -> A = A + B;
		// And ���� => �Ѵ� ���ƾ� ture ���� ������ false;
		bool b = true;
		b &= file == desc.file;
		b &= width == desc.width;
		b &= height == desc.height;
		
		return b;
	}
};


// Textures ���� �ؽ��� 
class Textures // �̹��� ������ 
{
private:
	static std::vector<TextureDesc> descs;


	//
public:
	friend class Texture;
private:
	static void Load(Texture* texture, D3DX11_IMAGE_LOAD_INFO* loadInfo = NULL);
public:
	static void Delete();
};

