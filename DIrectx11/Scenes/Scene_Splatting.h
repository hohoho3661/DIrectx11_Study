#pragma once
#include "Scene.h"

// Splatting ���´�.
class Scene_Splatting : public Scene
{
public:
	Scene_Splatting();
	~Scene_Splatting();
public:
	// Scene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;

private:
	class QuadObject* obj;
	class Shader* shader;
	class Transform* trans;

	//ID3D11ShaderResourceView* alphaTex[2];
	//ID3D11ShaderResourceView* baseTex[2];
	Texture* alphaTex;
	Texture* baseTexA;
	Texture* baseTexB;

};

