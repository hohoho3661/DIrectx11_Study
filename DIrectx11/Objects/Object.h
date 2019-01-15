#pragma once
class Object
{
public:
	Object();
	virtual ~Object();

	virtual void Update();
	virtual void Render();

	void Insfactor();

	void AddComponent(class Component* comp);
	void SetShader(class Shader* shader);
public:
	class Mesh* GetMesh() { return mesh; }
public:
	template<typename T>
	T* GetComponent()
	{
		T* result = NULL;
		for (class Component* comp : Components)
		{
			result = dynamic_cast<T*>(comp);
			if (result != NULL) return result;
		}
		return NULL;
	}

protected:
	bool bActive;

	class Mesh* mesh;
	class Shader* shader;

	vector<class Component*> Components;
};

