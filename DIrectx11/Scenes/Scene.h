#pragma once
class Scene
{
protected:
	bool bDelete = true;		// 삭제 여부 판단
public:
	friend class Scenes;
public:
	Scene();
	virtual ~Scene();
public:
	virtual void Init() =0;
	virtual void Release() =0;
	virtual void Update() = 0;
	virtual void PreRender() = 0;
	virtual void Render() = 0;

};
//////////////////////////////////////////////////////////////////////
// Scene Change
class Scenes
{
private:
	friend class Scene;
private:
	static class Scenes* instance;		// SingleTon
private:
	class Scene* nowScene;		// 플레이
	class Scene* releaseScene;	// 삭제 
	std::map<wstring, class Scene*> mapScene;

private:
	Scenes();
	~Scenes();
public:
	void Update();
	void Render();
	void PreRender();
public:
	static Scenes* Get();
	static void Delete();
	void SceneChange(wstring name);
	void AddScene(wstring name, Scene* scene);
};