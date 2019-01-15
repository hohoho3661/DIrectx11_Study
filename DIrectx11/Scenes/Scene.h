#pragma once
class Scene
{
protected:
	bool bDelete = true;		// ���� ���� �Ǵ�
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
	class Scene* nowScene;		// �÷���
	class Scene* releaseScene;	// ���� 
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