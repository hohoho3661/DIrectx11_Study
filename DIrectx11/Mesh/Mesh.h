#pragma once
class Mesh
{
public:
	Mesh(wstring file);
	virtual ~Mesh();

	virtual	void Update();
	virtual void Render();
protected:
	UINT strid;
	void* Data; //Vertex
	UINT VertexCount;

	UINT* Indices; //index
	UINT IndexCount;

	ID3D11Buffer* VertexBuffer;
	ID3D11Buffer* IndexBuffer;


	void CreateVertexBuffer(void* Data, UINT size);
	void CreateIndexBuffer();
public:
	void CopyVertices(void* vertices, UINT* count);
};

class Meshes
{
private: friend class Mesh;

public:
	template<typename T>
	static T* Load()
	{
		for (pair<wstring, Mesh*> temp : meshes)
		{
			if (T* result = dynamic_cast<T*>(temp.second))
			{
				return result;
			}
		}
		T* newMesh = new T;
		
		return newMesh;
	}
	static void Delete()
	{
		for (pair<wstring, Mesh*> temp : meshes)
		{
			SAFE_DELETE(temp.second);
		}
		meshes.clear();
	}
private:
	static map<wstring, Mesh*> meshes;

};

