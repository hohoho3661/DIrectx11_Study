#include "stdafx.h"
#include "Transform.h"


Transform::Transform()
{
	Buffer = new WorldBufferDesc;
	Reset();
}


Transform::~Transform()
{
	SAFE_DELETE(Buffer);
}

void Transform::Update()
{
	D3DXMATRIX World;
	D3DXMatrixIdentity(&World);

	//D3DXMatrixRotationZ;
	/*D3DXVECTOR2 rotateAxisX = 
	{
		cosf(D3DXToRadian(Angle)) ,
		-sinf(D3DXToRadian(Angle))
	};
	D3DXVECTOR2 rotateAxisY = 
	{
		sinf(D3DXToRadian(Angle)), 
		cosf(D3DXToRadian(Angle))
	};*/

	Right =
	{
		cosf(D3DXToRadian(Angle)) ,
		-sinf(D3DXToRadian(Angle))
	};
	Up =
	{
		sinf(D3DXToRadian(Angle)),
		cosf(D3DXToRadian(Angle))
	};



	D3DXVECTOR2 ScaleAxisX = Right * Scale.x;
	D3DXVECTOR2 ScaleAxisY = Up * Scale.y;
	//D3DXVECTOR2 ScaleAxisX = rotateAxisX * Scale.x;
	//D3DXVECTOR2 ScaleAxisY = rotateAxisY * Scale.y;

	// 
	memcpy(&World._11, &ScaleAxisX, sizeof(float) * 2);
	memcpy(&World._21, &ScaleAxisY, sizeof(float) * 2);
	memcpy(&World._41, &Position, sizeof(float) * 2);

	Buffer->World(World);
}

void Transform::Render()
{
	Buffer->SetVSBuffer(1);
}

void Transform::Reset(DWORD flag)
{
	if (flag & RESET_LOCATION)
	{
		Position = { 0.0f,0.0f };
	}
	if (flag & RESET_ROTATION)
	{
		Angle = 0.0f;
		Axis[0] = { 1.0f, 0.0f };
		Axis[1] = { 0.0f, 1.0f };
	}
	if (flag & RESET_SCALE)
	{
		Scale = { 1.0f,1.0f };
	}

}

void Transform::SetWorldPosition(float x, float y)
{
	SetWorldPosition(D3DXVECTOR2(x, y));
}

void Transform::SetWorldPosition(D3DXVECTOR2 vec)
{
	Position = vec;
}

D3DXVECTOR2 Transform::GetWorldPosition()
{
	return Position;
}

void Transform::SetRotation(float angle)
{
	Angle = angle;
}

void Transform::SetInspactor()
{
	ImGui::Checkbox("Transform", &bActive);
	ImGui::InputFloat2("Position", Position, 2);
	ImGui::InputFloat("Rotation", &Angle, 0.0f, 0.0f, 2);
	ImGui::InputFloat2("Scale", Scale, 2);
}


