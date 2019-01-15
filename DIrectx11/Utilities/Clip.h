#pragma once

// animation을 동작을 관리 , 
struct Frame
{
public:
	Frame(wstring file, float time = 0.3f,
		float startX = 0, float startY = 0,
		float endX = 1.0f, float endY = 1.0f)
		:Time(time), Start(startX, startY), 
		End(endX, endY), pNext(NULL)
	{
		Tex = new Texture(file);
	}
	class Texture* Tex;

	D3DXVECTOR2 Start;
	D3DXVECTOR2 End;

	float Time;

	Frame* pNext;
};

enum class AnimState
{
	End = 0,	//1번 동작
	Roop,		//반복동작
	Reverse		//0 ~ 5 -> 5 ~ 0 -> 0 ~ 5
};

class Clip
{
public:
	Clip(wstring name, AnimState state = AnimState::End);
	~Clip();

	void Update();
	void Render();

	void AddFrame(Frame* frame);

	void Play();
	void Stop();

private:
	friend class Animation;

	struct UVAnimDesc : BufferDesc
	{
	public:
		UVAnimDesc() : BufferDesc(&Data, sizeof(Struct)) {}
		void Set(D3DXVECTOR2 start, D3DXVECTOR2 end)
		{
			Data.Start = start; Data.End = end;
		}

	private:
		struct Struct
		{
			D3DXVECTOR2 Start;
			D3DXVECTOR2 End;
		}Data;
	}*AnimBuffer;

	struct SizeDesc : BufferDesc
	{
	public:
		SizeDesc() : BufferDesc(&Data, sizeof(Struct)){	}
		void Set(float Width, float Height)
		{
			Data.Size.x = Width;
			Data.Size.y = Height;
		}

	private:
		struct Struct
		{
			D3DXVECTOR2 Size;
			D3DXVECTOR2 Padding;
		}Data;
	}*SizeBuffer;
private:
	Frame* pHead;	 // Frame의 첫 주소 
	Frame* pCurrent; //현재 프레임

	float totalTime; //총시간 
	float time; //교체 시간

	wstring name;
	AnimState state;

	bool bPlay = false;
};

