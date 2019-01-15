#pragma once

//  싱글턴(다이나믹) 
//struct TextureInfo
//{
//	ID3D11ShaderResourceView* SRV;
//	D3DX11_IMAGE_INFO Info;
//};
// SRV-> 셰이더에게 보내는 데이터 
// Texture2D-> 이미지 데이터 

class Texture // 이미지 한장
{
private:
	wstring file;
	TexMetadata metaData; // 텍스쳐 정보 (색상 정보 ) DirextXTex에 들어갈 수 있는 해더 속성 (변환)
	ID3D11ShaderResourceView* view;

public:
	// Load 텍스쳐가 가지고 있는 private ~ public 까지 public 에서 사용 가능
	friend class Textures;
	//
public:
	Texture(wstring file, D3DX11_IMAGE_LOAD_INFO* loadinfo = NULL);
	~Texture();

public:
	static void SaveFile(wstring file, ID3D11Texture2D* src);
	//DXGI_FORMAT : 크기에 따라 이미지 형식이 달라진다. 
	// ID3D11Texture* 포인터가 들어간다. (I : 순수가상함수로 되어 있고,  Iterator 타입 )  순수가상함수가 1개라도 있을 경우 new가 안된다. 
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
	operator ID3D11ShaderResourceView* () { return  view; }		// ex) Texture* temp; temp(); -> view return ; // 변하지 않는 주소값 
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
		// And 연산 => 둘다 같아야 ture 같지 않으면 false;
		bool b = true;
		b &= file == desc.file;
		b &= width == desc.width;
		b &= height == desc.height;
		
		return b;
	}
};


// Textures 여러 텍스쳐 
class Textures // 이미지 관리용 
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

