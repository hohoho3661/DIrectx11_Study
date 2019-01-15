#pragma once
#include "Component.h"
class Animation : public Component
{
public:
	Animation();
	~Animation();

	void Update();
	void Render();

	void AddClip(class Clip* clip);

	void Play(wstring name);
private:
	map<wstring, class Clip*> Clips;

	class Clip* current;

	// Component��(��) ���� ��ӵ�
	virtual void SetInspactor() override;
};

