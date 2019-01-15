#include "stdafx.h"
#include "Scene.h"


Scene::Scene()
{
}


Scene::~Scene()
{
}




//////////////////////////////////////////////////

Scenes* Scenes::instance = NULL;

Scenes::Scenes()
	: nowScene(NULL), releaseScene(NULL)
{
}

Scenes::~Scenes()
{
	if (releaseScene != NULL)
	{
		releaseScene->Release();
		SAFE_DELETE(releaseScene);
	}

	if (nowScene != NULL)
	{
		nowScene->Release();
		SAFE_DELETE(nowScene);
	}

	for (pair<wstring, Scene*> temp : mapScene)
	{
		if (temp.second != NULL)
		{
			temp.second->Release();
			SAFE_DELETE(temp.second);

		}
	}
	Delete();
}

void Scenes::Update()
{
	if (releaseScene != NULL)
	{
		if (releaseScene->bDelete)
		{
			releaseScene->Release();
		}

		releaseScene = NULL;
	}

	if (nowScene != NULL)
	{
		nowScene->Update();
	}
}

void Scenes::Render()
{
	if (nowScene)
	{
		nowScene->Render();
	}
}

void Scenes::PreRender()
{
	if (nowScene)
	{
		nowScene->PreRender();
	}
}

Scenes * Scenes::Get()
{
	if (instance == NULL)
	{
		instance = new Scenes();
	}
	return instance;
}

void Scenes::Delete()
{
	SAFE_DELETE(instance);
}

void Scenes::SceneChange(wstring name)
{
	//auto iter = mapScene.find(name);
	map<wstring,Scene*>::iterator iter = mapScene.find(name);

	if (iter == mapScene.end())
	{
		assert(false);
	}

	if (nowScene != NULL)
	{
		releaseScene = nowScene;
		nowScene = iter->second;

		if (nowScene->bDelete)
		{
			nowScene->Init();
		}
	}
	else
	{
		nowScene = iter->second;
	}

	

	

}

void Scenes::AddScene(wstring name, Scene * scene)
{
	if (mapScene.count(name) > 0)
	{
		assert(false);
	}
	scene->Init();
	mapScene[name] = scene;
}
