#include "stdafx.h"
#include "Intersect.h"
#include "./Mesh/Quad.h"
#include "./Components/BoxCollider.h"
#include "./Components/Transform.h"
#include "./Objects/Object.h"
///--------------------------------------------------------------------------------
/// AABB Collision
/// return : result
/// comp1  : Rect1
/// comp2  :  "  2
/// W1	   : World of Rect1
/// w2     :  "     "   " 2
///--------------------------------------------------------------------------------
bool Intersect::IsConstainsRect(Quad * comp1, D3DXMATRIX W1, Quad * comp2, D3DXMATRIX W2)
{
	D3DXVECTOR2 MinA, MaxA;
	D3DXVECTOR2 MinB, MaxB;

	Intersect::GetMinMax(&MinA, &MaxA, comp1, W1);
	Intersect::GetMinMax(&MinB, &MaxB, comp2, W2);

	bool bHorizontal = false;
	bool bVertical = false;

	if (MinA.x <= MaxB.x && MaxA.x >=MinB.x)
	{
		bHorizontal = true;
	}
	if (MinA.y <= MaxB.y && MaxA.y >= MinB.y)
	{
		bVertical = true;
	}

	if (bHorizontal && bVertical)
	{
		RECT rc;

		rc.left   = (MinA.x < MinB.x) ? MinB.x : MinA.x;
		rc.bottom = (MinA.y < MinB.y) ? MinA.y : MinB.y;
		rc.right  = (MaxA.x < MaxB.x) ? MaxA.x : MaxB.x;
		rc.top	  = (MaxA.y < MaxB.y) ? MaxB.y : MaxA.y;

		return true;
	}
	return false;
}

bool Intersect::ObbCollision(BoxCollider * coll1, BoxCollider * coll2)
{
	OBB_Info obbA, obbB;

	coll1->SetObbInfo(obbA);
	coll2->SetObbInfo(obbB);

	// 얼마만큼 이동 및 회전 했는지 확인 해야 한다. 
	float fCos[2][2];			// [x][y]	
	float fAbsCos[2][2];		// 절대값 
	float fDistance[2];			//

	//
	D3DXVECTOR2 d = obbA.vOrgCenterPos - obbB.vOrgCenterPos;

	//cos a or b 

	for (int a = 0; a < 2; a++)
	{
		for (int b = 0; b < 2; b++)
		{
			fCos[a][b] = D3DXVec2Dot(&obbA.vOrgAxisDir[a], &obbB.vOrgAxisDir[b]);
			fAbsCos[a][b] = fabs(fCos[a][b]);
		}

		fDistance[a] = D3DXVec2Dot(&obbA.vOrgAxisDir[a], &d);

		float r = fabs(fDistance[a]);

		float r1 = obbA.faxisHalfLength[a];
		float r2 = obbB.faxisHalfLength[0] + fAbsCos[a][0] + obbB.faxisHalfLength[1] + fAbsCos[a][1];	// 투형한 길이값 

		if (r > r1 + r2)
		{
			return false;
		}
	}

	for (int b = 0; b < 2; b++)
	{
		//for (int a = 0; a < 2; a++)
		//{
		//	fCos[a][b] = D3DXVec2Dot(&obbA.vOrgAxisDir[a], &obbB.vOrgAxisDir[b]);
		//	fAbsCos[a][b] = fabs(fCos[a][b]);
		//}

		fDistance[b] = D3DXVec2Dot(&obbA.vOrgAxisDir[b], &d);

		float r = fabs(fDistance[b]);

		float r1 = obbB.faxisHalfLength[b];
		float r2 = obbA.faxisHalfLength[0] + fAbsCos[0][b] + obbA.faxisHalfLength[1] + fAbsCos[1][b];	// 투형한 길이값 

		if (r > r1 + r2)
		{
			return false;
		}
	}


	return true;
}

void Intersect::Blocking(BoxCollider * coll1, BoxCollider * coll2)
{
	//if (!ObbCollision(coll1, coll2))
	//{
	//	return;
	//}

	//
	D3DXVECTOR2 minMaxA[2];
	D3DXVECTOR2 minMaxB[2];

	if (!IsConstainsRect((Quad*)coll1->GetGameObject()->GetMesh(), coll1->GetWorld(),
		(Quad*)coll2->GetGameObject()->GetMesh(), coll2->GetWorld()))
	{
		return;
	}
	// 도형이 가지고 있는 크기 
	D3DXVECTOR2 localPosA[4];
	D3DXVECTOR2 localPosB[4];


	GetMinMax(&minMaxA[0], &minMaxA[1], (Quad*)coll1->GetGameObject()->GetMesh(),
		coll1->GetWorld());

	GetMinMax(&minMaxB[0], &minMaxB[1], (Quad*)coll2->GetGameObject()->GetMesh(),
		coll2->GetWorld());

	//  1   2
	//  0   3
	localPosA[0] = { minMaxA[0].x, minMaxA[0].y };
	localPosA[1] = { minMaxA[0].x, minMaxA[1].y };
	localPosA[2] = { minMaxA[1].x, minMaxA[1].y };
	localPosA[3] = { minMaxA[1].x, minMaxA[0].y };



	//coll1->GetGameObject()->GetMesh()->CopyVertices(&localPosA, NULL);
	//coll2->GetGameObject()->GetMesh()->CopyVertices(&localPosB, NULL);


	//

	Transform* transA = coll1->GetTransform();
	Transform* transB = coll2->GetTransform();

	D3DXMATRIX invWorldA, invWorldB;	// 

	D3DXMatrixInverse(&invWorldA, NULL, &transA->World());
	D3DXMatrixInverse(&invWorldB, NULL, &transB->World());

	D3DXMATRIX mat = transB->World() * invWorldA;

	D3DXVECTOR2 pos[4];
	for (int i = 0; i < 4; i++)
	{
		D3DXVec2TransformCoord(&pos[i], &localPosA[i], &mat);
	}


	// b가 회전이 될수도 있어서 기준을 잡아준다. 
	minMaxA[0] = pos[0];
	minMaxA[1] = pos[0];

	for (int i = 1; i < 4; i++)
	{
		// 최소값
		if (minMaxA[0].x > pos[i].x)
		{
			minMaxA[0].x = pos[i].x;
		}

		minMaxA[0].y = min(minMaxA[0].y, pos[i].y);

		// 최대값
		minMaxA[1].x = max(minMaxA[1].y, pos[i].y);
		minMaxA[1].y = max(minMaxA[1].y, pos[i].y);

	}

	// 사각형
	struct fRect
	{
		float left;
		float right;
		float top;
		float bottom;
	};


	fRect rcA = { minMaxA[0].x, minMaxA[1].x , minMaxA[1].y , minMaxA[0].y };
	fRect rcB = { minMaxB[0].x, minMaxB[1].x , minMaxB[1].y , minMaxB[0].y };

	// 겹쳐진 사각형
	fRect rcInter;

	rcInter.left = max(rcA.left, rcB.left);
	rcInter.right = min(rcA.right, rcB.right);
	rcInter.top = min(rcA.top, rcB.top);
	rcInter.bottom = min(rcA.bottom, rcB.bottom);

	
	float interX = rcInter.right - rcInter.left;
	float interY = rcInter.top - rcInter.bottom;

	float minInter = (interX < interY) ? interX : interY;



}

void Intersect::GetMinMax(D3DXVECTOR2 * OutMin, D3DXVECTOR2 * OutMax, Quad * comp, D3DXMATRIX World)
{
	D3DXVECTOR3 Position[4];
	comp->GetVertices(Position);
	for (int i = 0; i < 4; i++)
	{
		D3DXVec3TransformCoord(&Position[i],&Position[i], &World);
	}

	*OutMax = { Position[0].x, Position[0].y };
	*OutMin = { Position[0].x, Position[0].y };

	for (int i = 1; i < 4; i++)
	{
		if (OutMax->x < Position[i].x) OutMax->x = Position[i].x;
		if (OutMax->y < Position[i].y) OutMax->y = Position[i].y;

		if (OutMin->x > Position[i].x) OutMin->x = Position[i].x;
		if (OutMin->y > Position[i].y) OutMin->y = Position[i].y;
	}
}
