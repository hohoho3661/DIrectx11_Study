#pragma once

#include "Component.h"

// �浹ü 


class BoxCollider : public Component
{
private:
	D3DXVECTOR3 center;
	D3DXVECTOR3 scale;
	D3DXMATRIX world;

private:
	class Transform* transform;
	class Line* line[4];
	class Object* object;
public:
	BoxCollider(class Object* obj);
	~BoxCollider();

public:
	void Update() override;
	void Render() override;
public:
	void Center(float x, float y);
	void Scale(float x, float y);
public:
	virtual void SetInspactor() override;

	void SetObbInfo(struct OBB_Info& obb);
	class Transform* GetTransform() { return transform; }
	D3DXMATRIX GetWorld() { return world; }
	class Object* GetGameObject() { return object; }
};

