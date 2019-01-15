#include "stdafx.h"
#include "BoxCollider.h"
#include "./Objects/Object.h"
#include "./Mesh/Mesh.h"
#include "./Components/Transform.h"
#include "./Utilities/Gizmo.h"
#include "./Utilities/Intersect.h"

BoxCollider::BoxCollider(Object * obj)
{
	object = obj;
	transform = obj->GetComponent<Transform>();
	//UINT count;
	//VertexTexture* vertices;
	//obj->GetMesh()->CopyVertices(vertices, &count);

	//if (count == 4)
	//{
	//	for (int i = 0; i < 4; i++)
	//	{
	//		line[i] =new  Line(vertices[i - 1].Position, vertices[i].Position);
	//	}
	//}

	line[0] = new Line(D3DXVECTOR3(-50, -50, 0), D3DXVECTOR3(50, -50, 0));
	line[1] = new Line(D3DXVECTOR3(50, -50, 0), D3DXVECTOR3(50, 50, 0));
	line[2] = new Line(D3DXVECTOR3(-50, 50, 0), D3DXVECTOR3(50, 50, 0));
	line[3] = new Line(D3DXVECTOR3(-50, 50, 0), D3DXVECTOR3(-50, -50, 0));



	// 
	center = { 0.f,0.f,0.f };
	scale = { 1.f,1.f,1.f };

}

BoxCollider::~BoxCollider()
{
	for (Line* temp : line)
	{
		SAFE_DELETE(temp);
	}
}

void BoxCollider::Update()
{
	if (bActive == false)
	{
		return;
	}
	D3DXMATRIX s, t;

	D3DXMatrixScaling(&s, scale.x, scale.y, scale.z);
	D3DXMatrixTranslation(&t, center.x, center.y, center.z);

	// 행렬 곱 s(크기) * r(회전) * t(이동)  -> Obj 관계에 부모자식 관계 
	world = s * t * transform->World();
	//for (int i = 0; i < 4; i++)
	//{
	//	line[i]->World(world);
	//}

}

void BoxCollider::Render()
{
#ifdef _DEBUG
	if (bActive == false)
	{
		return;
	}
	for (int i = 0; i < 4; i++)
	{
		line[i]->World(world);
		line[i]->Render();
	}
#endif // _DeBUG
}

void BoxCollider::Center(float x, float y)
{
	center = { x,y,0.0f };
}

void BoxCollider::Scale(float x, float y)
{
	scale = { x,y,1.0f };
}

void BoxCollider::SetInspactor()
{
}

void BoxCollider::SetObbInfo(OBB_Info & obb)
{
	obb.vOrgCenterPos = { world._41 , world._42 };
	
	D3DXVECTOR2 right ={ world._11, world._12 };
	D3DXVECTOR2 up = { world._21, world._22 };
	
	obb.vOrgAxisDir[0] = right;
	obb.vOrgAxisDir[1] = up;
	
	D3DXVec2Normalize(&obb.vOrgAxisDir[0], &right);
	D3DXVec2Normalize(&obb.vOrgAxisDir[1], &up);

	obb.fAxisLength[0] = D3DXVec2Length(&right);
	obb.fAxisLength[1] = D3DXVec2Length(&up);

	obb.faxisHalfLength[0] = obb.fAxisLength[0] / 2;
	obb.faxisHalfLength[1] = obb.fAxisLength[1] / 2;


}
