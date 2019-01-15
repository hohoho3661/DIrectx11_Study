#pragma once

#define MAX_INPUT_MOUSE 8


class Mouse
{

private:
	Mouse();
	~Mouse();
private:
	static Mouse* instance;
	D3DXVECTOR3 position;
private:

	//
	enum class InputStatus
	{
		NONE = 0, 
		DOWN,
		UP,
		PRESS,
		DBLCLK,
	};
	
	byte buttonStatus[MAX_INPUT_MOUSE];
	byte buttonOldStatus[MAX_INPUT_MOUSE];
	byte buttonMap[MAX_INPUT_MOUSE];

	D3DXVECTOR3 wheelStatus;
	D3DXVECTOR3 wheelOldStatus;
	D3DXVECTOR3 wheelMoveValue;

	DWORD timeDblclk;
	DWORD startDbclk[MAX_INPUT_MOUSE];
	int buttonCount[MAX_INPUT_MOUSE];

	
public:
	static Mouse* Get();
	static void Delete();
	LRESULT CALLBACK InputProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	void Update();


public:
	D3DXVECTOR3 GetPosition() { return position; }

	//
	bool Down(DWORD button)
	{
		return buttonMap[button] == (byte)InputStatus::DOWN;
	}

	bool Up(DWORD button)
	{
		return buttonMap[button] == (byte)InputStatus::UP;
	}
	bool Press(DWORD button)
	{
		return buttonMap[button] == (byte)InputStatus::PRESS;
	}
	bool Dblclk(DWORD button)
	{
		return buttonMap[button] == (byte)InputStatus::DBLCLK;
	}

	//
	D3DXVECTOR3 GetMouseValue()
	{
		return wheelMoveValue;
	}

};

