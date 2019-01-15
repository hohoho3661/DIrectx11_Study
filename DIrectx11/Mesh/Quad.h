#pragma once
#include "./Mesh.h"
class Quad : public Mesh
{
public:
	Quad();
	~Quad();

	void Update() override;
	void Render() override;

	void GetVertices(D3DXVECTOR3* Position);

private:
	VertexTexture* vertices;

};

