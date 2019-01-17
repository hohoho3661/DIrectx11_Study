#pragma once

struct BufferDesc
{
public:
	BufferDesc(void* data, UINT size)
		:Data(data), Size(size)
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.ByteWidth = size;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.Usage = D3D11_USAGE_DYNAMIC;

		HRESULT hr = D2D::Get()->GetDevice()->CreateBuffer
		(
			&desc, NULL, &Buffer
		);
		assert(SUCCEEDED(hr));
	}

	void SetPSBuffer(UINT slot)
	{
		Map(Data, Size);
		D2D::Get()->GetDC()->PSSetConstantBuffers(slot, 1, &Buffer);
	}
	void SetVSBuffer(UINT slot)
	{
		Map(Data, Size);
		D2D::Get()->GetDC()->VSSetConstantBuffers(slot, 1, &Buffer);
	}
	void SetDSBuffer(UINT slot)
	{
		Map(Data, Size);
		D2D::GetDC()->DSSetConstantBuffers(slot, 1, &Buffer);
	}
private:
	void* Data;
	UINT Size;
	ID3D11Buffer* Buffer;

	void Map(void* data, UINT size)
	{
		D3D11_MAPPED_SUBRESOURCE map;
		D2D::Get()->GetDC()->Map(Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &map);
		{
			memcpy(map.pData, data, size);
		}
		D2D::Get()->GetDC()->Unmap(Buffer, 0);
	}
};