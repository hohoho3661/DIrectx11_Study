#pragma once

struct OBB_Info
{
	// 중심점
	D3DXVECTOR2 vOrgCenterPos;			// TransForm pos
	// 방향 
	D3DXVECTOR2 vOrgAxisDir[2];			// TransForm Right Up


	// 스케일이 들어간 길이값 , 길이에 대한 절반 값 
	float fAxisLength[2];				// 축 * 스케일
	float faxisHalfLength[2];			// (축 * 스케일 ) / 2 

	//
	D3DXVECTOR2 vMin, vMax;


};


class Intersect
{
public:
	static bool IsConstainsRect(
		class Quad* comp1, D3DXMATRIX W1,
		class Quad* comp2, D3DXMATRIX W2);
	//
	static bool ObbCollision(
		class BoxCollider* coll1, class BoxCollider* coll2
	);

	static void Blocking(class BoxCollider* coll1, class BoxCollider* coll2);
private:
	static void GetMinMax(D3DXVECTOR2* OutMin, D3DXVECTOR2* OutMax,
		class Quad* comp, D3DXMATRIX World);

};

