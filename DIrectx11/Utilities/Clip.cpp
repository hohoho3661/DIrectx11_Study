#include "stdafx.h"
#include "Clip.h"


Clip::Clip(wstring name, AnimState state)
	: name(name)
	, state(state)
	, pHead(NULL)
	, pCurrent(NULL)
	, totalTime(0.0f)
	, time(0.0f)
{
	AnimBuffer = new UVAnimDesc();
	SizeBuffer = new SizeDesc();
}

Clip::~Clip()
{
	SAFE_DELETE(AnimBuffer);
	SAFE_DELETE(SizeBuffer);

	while (pHead != NULL)
	{
		pCurrent = pHead;
		pHead = pHead->pNext;
		SAFE_DELETE(pCurrent);
	}
}

void Clip::Update()
{
	if (!bPlay) return;

	AnimBuffer->Set(pCurrent->Start, pCurrent->End);
	SizeBuffer->Set
	(
		pCurrent->Tex->GetWidth(),
		pCurrent->Tex->GetHeight()
	);
	time += 0.01f; //½Ã°£
	if (pCurrent->Time > time) return;

	switch (state)
	{
	case AnimState::End:
		pCurrent = pCurrent->pNext;
		if (pCurrent == NULL) Stop();
		break;
	case AnimState::Roop:
		pCurrent = pCurrent->pNext;
		if (pCurrent == NULL) pCurrent = pHead;
		break;
	case AnimState::Reverse:
		break;
	}
}

void Clip::Render()
{
	AnimBuffer->SetVSBuffer(2);
	SizeBuffer->SetVSBuffer(3);
	D2D::Get()->GetDC()->PSSetShaderResources(0, 1, pCurrent->Tex->GetView());
}

void Clip::AddFrame(Frame * frame)
{
	if (pHead == NULL) pHead = frame;
	else
	{
		pCurrent = pHead;
		while (pCurrent->pNext != NULL)
		{
			pCurrent = pCurrent->pNext;
		}
		pCurrent->pNext = frame;
		pCurrent = NULL;
	}
}

void Clip::Play()
{
	pCurrent = pHead;
	bPlay = true;
}

void Clip::Stop()
{
	//pCurrent = NULL;
	bPlay = false;
}
