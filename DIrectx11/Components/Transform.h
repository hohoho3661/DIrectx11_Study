#pragma once
#include "Component.h"
#define RESET_LOCATION 1 //Position, Coord, Location
#define RESET_ROTATION 2 // rotate(축회전), rotation(사원수 회전)
#define RESET_SCALE	   4 

class Transform : public Component
{
public:
	Transform();
	~Transform();

	void Update();
	void Render();

	void Reset(DWORD flag = RESET_LOCATION | RESET_ROTATION | RESET_SCALE);

	void SetWorldPosition(float x, float y);
	void SetWorldPosition(D3DXVECTOR2 vec);

	D3DXVECTOR2 GetWorldPosition();
	D3DXVECTOR2 GetScale() { return Scale; }
	D3DXVECTOR2 GetRight() { return Right; }
	D3DXVECTOR2 GetUp() { return Up; }


	void SetRotation(float angle);
	D3DXMATRIX World() { return Buffer->World(); }

private:
	struct WorldBufferDesc : BufferDesc
	{
	public:
		WorldBufferDesc() : BufferDesc(&Data, sizeof(Struct))
		{
			D3DXMatrixIdentity(&Data.World);
		}
		void World(D3DXMATRIX world)
		{
			Data.World = world;
			D3DXMatrixTranspose(&Data.World, &Data.World);
		}
		D3DXMATRIX World()
		{
			D3DXMATRIX result;
			D3DXMatrixTranspose(&result, &Data.World);
			return result;
		}
	private:
		struct Struct
		{
			D3DXMATRIX World;
		}Data;
	}*Buffer;

private:
	D3DXVECTOR2 Position;
	float Angle;
	D3DXVECTOR2 Scale;
	union 
	{
		struct
		{
			D3DXVECTOR2 Axis[2];
		};
		struct
		{
			D3DXVECTOR2 Right;
			D3DXVECTOR2 Up;
		};
	};

	// Component을(를) 통해 상속됨
	virtual void SetInspactor() override;
};

