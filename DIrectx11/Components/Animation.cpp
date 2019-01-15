#include "stdafx.h"
#include "Animation.h"
#include "./Utilities/Clip.h"

Animation::Animation()
	:current(NULL)
{
}


Animation::~Animation()
{
	for (auto temp : Clips)
	{
		SAFE_DELETE(temp.second);
	}
	Clips.clear();
}

void Animation::Update()
{
	if (current == NULL) return;

	current->Update();
}

void Animation::Render()
{
	if (current == NULL) return;
	current->Render();
}

void Animation::AddClip(Clip * clip)
{
	if (Clips.count(clip->name) > 0)
	{
		assert(false && "Clips Already have Same key");
	}

	Clips[clip->name] = clip;
}

void Animation::Play(wstring name)
{
	auto iter = Clips.find(name);
	if (iter == Clips.end()) assert(false && "Clips not have key");

	current = iter->second;
	current->Play();
}

void Animation::SetInspactor()
{
}
