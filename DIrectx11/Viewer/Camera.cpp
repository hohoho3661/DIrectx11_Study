#include "stdafx.h"
#include "Camera.h"
#include "./Render/RenderTargetTexture.h"

Camera::Camera()
{
	//view
	D3DXMatrixLookAtLH
	(
		&Data.View,	//return 
		new D3DXVECTOR3(0, 0, 0), //ī�޶� ��ġ 
		new D3DXVECTOR3(0, 0, 1), //�ٶ� ���� ���� 
		new D3DXVECTOR3(0, 1, 0)  //ī�޶��� �ܼ��� ������ 
	);

	//{1 , 0 , 0}		{1 , 0 , 1}
	//{0 , 1 , 0}  =>	{0 , 1 , 1} 
	//{1 , 1 , 1}		{0 , 0 , 1}
	//��ġ ��� 
	D3DXMatrixTranspose(&Data.View, &Data.View);

	//D3DXMatrixPerspectiveFovLH - ���� ����
	//Ortho - ���� ����
	D3DXMatrixOrthoOffCenterLH
	(
		&Data.Ortho,
		0, desc.Width, 0, desc.Height,0.0f,1.0f
	);



	D3DXMatrixTranspose(&Data.Ortho, &Data.Ortho);

	D3D11_BUFFER_DESC bufferDesc = { 0 };
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; //���̴� cBuffer �뵵
	bufferDesc.ByteWidth = sizeof(ViewOrthoDesc);
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;


	D2D::Get()->GetDevice()->CreateBuffer
	(
		&bufferDesc, NULL , &buffer
	);

	D3D11_MAPPED_SUBRESOURCE mappedSubresource;
	D2D::Get()->GetDC()->Map
	(
		buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource
	);
	memcpy(mappedSubresource.pData, &Data, sizeof(ViewOrthoDesc));

	D2D::Get()->GetDC()->Unmap(buffer, 0);

	RTT = new RenderTargetTexture();
}


Camera::~Camera()
{
	SAFE_RELEASE(buffer);
	SAFE_DELETE(RTT);
}

void Camera::Render()
{
	if (GetAsyncKeyState(VK_LSHIFT) & 0x8000)
	{
		if (GetAsyncKeyState(VK_F3) & 0x8000)
			RTT->SaveTexture(L"RTT.png");
	}

	D2D::Get()->GetDC()->VSSetConstantBuffers(0, 1, &buffer);
}

void Camera::View(D3DXMATRIX * mat)
{
	memcpy(mat, &Data.View, sizeof(D3DXMATRIX));
}

void Camera::Ortho(D3DXMATRIX * mat)
{
	memcpy(mat, &Data.Ortho, sizeof(D3DXMATRIX));
}

void Camera::SetRTT(ID3D11ShaderResourceView ** srv)
{
	if (srv == NULL) return;
	*srv = RTT->Texture();
}

void Camera::Target()
{
	RTT->Clear(0xFFFFFF00);
}
