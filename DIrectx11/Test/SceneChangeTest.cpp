#include "stdafx.h"
#include "SceneChangeTest.h"
#include "./System/Mouse.h"

SceneChangeTest::SceneChangeTest()
{
}


SceneChangeTest::~SceneChangeTest()
{
}

void SceneChangeTest::Init()
{
}

void SceneChangeTest::Release()
{
}

void SceneChangeTest::Update()
{
	if (Mouse::Get()->Down(1))
	{
		Scenes::Get()->SceneChange(L"Scene_1");
	}
}

void SceneChangeTest::PreRender()
{
}

void SceneChangeTest::Render()
{
}
