#pragma once

struct OBB_Info
{
	// �߽���
	D3DXVECTOR2 vOrgCenterPos;			// TransForm pos
	// ���� 
	D3DXVECTOR2 vOrgAxisDir[2];			// TransForm Right Up


	// �������� �� ���̰� , ���̿� ���� ���� �� 
	float fAxisLength[2];				// �� * ������
	float faxisHalfLength[2];			// (�� * ������ ) / 2 

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

