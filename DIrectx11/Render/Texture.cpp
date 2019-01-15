#include "stdafx.h"
#include "Texture.h"


// static 으로 선언으로 한 변수들은 해더에서만 가능하다.
std::vector<TextureDesc> Textures::descs;

Texture::Texture(wstring file, D3DX11_IMAGE_LOAD_INFO* loadinfo)
	: file(file)
{
	Textures::Load(this, loadinfo);
}

Texture::~Texture()
{
}

void Texture::SaveFile(wstring file, ID3D11Texture2D * src)
{

}

D3D11_TEXTURE2D_DESC Texture::ReadPixels(IN ID3D11Texture2D * src, IN DXGI_FORMAT readFormat, OUT std::vector<D3DXCOLOR>* pixels)
{
	return D3D11_TEXTURE2D_DESC();
}


void Texture::SaveFile(wstring file)
{
}

D3D11_TEXTURE2D_DESC Texture::ReadPixels(DXGI_FORMAT readFormat, std::vector<D3DXCOLOR>* pixels)
{
	return D3D11_TEXTURE2D_DESC();
}



//------------------------------------------------------------------------------------------------------------------
// Textures 
//------------------------------------------------------------------------------------------------------------------
void Textures::Load(Texture * texture, D3DX11_IMAGE_LOAD_INFO * loadInfo)
{
	HRESULT hr; // 확인용 

	TexMetadata metaData;
	// 확장자 
	// 경로는 / , 확자는 . 
	size_t index = texture->file.find_last_of('.');
	wstring ext = texture->file.substr(index+1 , texture->file.length());

	if (ext == L"dds")
	{
		hr = GetMetadataFromDDSFile(texture->file.c_str(),	// 경로/이름.확장자
			DDS_FLAGS_NONE,// 옵션
			OUT metaData // 반환값
		);
	}
	else
	{
		hr = GetMetadataFromWICFile(texture->file.c_str(),
			WIC_FLAGS_NONE,
			metaData);
	}
	assert(SUCCEEDED(hr));
	
	UINT width = metaData.width;
	UINT height = metaData.height;

	if (loadInfo != NULL)
	{
		width = loadInfo->Width;
		height = loadInfo->Height;

		metaData.width = loadInfo->Width;
		metaData.height = loadInfo->Height;

	}


	// metaData 1픽셀당 ... 정보를 가지고 있는 
	// 쉐이더에게 보내는 구조체
	TextureDesc desc;
	desc.file = texture->file;
	desc.width = width;
	desc.height = height;

	//
	TextureDesc exist;

	bool bExist = false;

	for (TextureDesc temp : descs)
	{
		if (desc == temp)
		{
			bExist = true;
			exist = temp;
			break;
		}
	}

	if (true == bExist)
	{
		texture->metaData = exist.metaData;
		texture->view = exist.view;
	}
	else
	{
		ScratchImage image;
		if (ext == L"dds")
		{
			hr = LoadFromDDSFile(texture->file.c_str(),
				DDS_FLAGS_NONE,
				&metaData,
				image
			);
			assert(SUCCEEDED(hr));		// 현재 파일 위치에서 라인 ...에서 에러가 났습니다. 에러 이유 안에 있는 조건이 충족되지 않았습니다...
		}
		else
		{
			hr = LoadFromWICFile(texture->file.c_str(),
				WIC_FLAGS_NONE,
				&metaData, image
			);

			assert(SUCCEEDED(hr));
		}

		// 쉐이더에게 보내기 위해...
		ID3D11ShaderResourceView* view;
		hr = CreateShaderResourceView(D2D::GetDevice(),
			image.GetImages(),
			image.GetImageCount(),
			metaData,
			&view
		);

		assert(SUCCEEDED(hr));

		desc.file = texture->file;
		desc.width = metaData.width;
		desc.height = metaData.height;
		desc.view = view;

		texture->view = view;
		texture->metaData = metaData;

		descs.push_back(desc);

	}
}

void Textures::Delete()
{
	// 시작 부터 마지막 까지 돌리는 문법
	for (TextureDesc Desc : descs)
	{
		SAFE_RELEASE(Desc.view);
	}
}


