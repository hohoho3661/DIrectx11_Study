#pragma once
#include "./Scenes/Scene.h"

class SceneChangeTest : public Scene
{
public:
	SceneChangeTest();
	~SceneChangeTest();

	// Scene�� ���� ��ӵ�.
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
};

