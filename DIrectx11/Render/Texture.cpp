#include "stdafx.h"
#include "Texture.h"


// static ���� �������� �� �������� �ش������� �����ϴ�.
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
	HRESULT hr; // Ȯ�ο� 

	TexMetadata metaData;
	// Ȯ���� 
	// ��δ� / , Ȯ�ڴ� . 
	size_t index = texture->file.find_last_of('.');
	wstring ext = texture->file.substr(index+1 , texture->file.length());

	if (ext == L"dds")
	{
		hr = GetMetadataFromDDSFile(texture->file.c_str(),	// ���/�̸�.Ȯ����
			DDS_FLAGS_NONE,// �ɼ�
			OUT metaData // ��ȯ��
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


	// metaData 1�ȼ��� ... ������ ������ �ִ� 
	// ���̴����� ������ ����ü
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
			assert(SUCCEEDED(hr));		// ���� ���� ��ġ���� ���� ...���� ������ �����ϴ�. ���� ���� �ȿ� �ִ� ������ �������� �ʾҽ��ϴ�...
		}
		else
		{
			hr = LoadFromWICFile(texture->file.c_str(),
				WIC_FLAGS_NONE,
				&metaData, image
			);

			assert(SUCCEEDED(hr));
		}

		// ���̴����� ������ ����...
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
	// ���� ���� ������ ���� ������ ����
	for (TextureDesc Desc : descs)
	{
		SAFE_RELEASE(Desc.view);
	}
}


