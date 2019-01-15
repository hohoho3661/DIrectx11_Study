#pragma once

class Line
{
private:
	struct WorldDesc : public BufferDesc
	{
	private:
		D3DXMATRIX world;
		struct strData
		{
			D3DXMATRIX world;
		}Data;
	public:
		WorldDesc() : BufferDesc(&Data, sizeof(strData))
		{
			D3DXMatrixIdentity(&Data.world);
		}
		void Set(D3DXMATRIX w)
		{
			// ��ġ ��� -> D11������ ����� ���η� �б� ������ ������ ������ ���� �Ѵ�. 
			D3DXMatrixTranspose(&w, &w);
			Data.world = w;

		}
	};
	//
	struct ColorDesc : public BufferDesc
	{
	private:
		struct strData
		{
			D3DXCOLOR color;

		}Data;
	public:
		ColorDesc() : BufferDesc(&Data, sizeof(strData))
		{
			// 0x-> 16 A R G B 
			Data.color = 0xff00ff00;
		}
	};
private:
	class Shader* shader;
	WorldDesc* worldBuffer;
	ColorDesc* colorBuffer;
	ID3D11Buffer* vertexBuffer;
public:
	Line(D3DXVECTOR3 start, D3DXVECTOR3 end);
	~Line();
public:
	void Update();
	void Render();
public:
	void World(D3DXMATRIX world);

};