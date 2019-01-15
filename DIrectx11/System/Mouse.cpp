#include "stdafx.h"
#include "Mouse.h"

Mouse* Mouse::instance = NULL;


Mouse::Mouse()
{
	position = D3DXVECTOR3(0, 0, 0);

	wheelStatus = D3DXVECTOR3(0, 0, 0);
	wheelOldStatus = D3DXVECTOR3(0, 0, 0);
	wheelMoveValue = D3DXVECTOR3(0, 0, 0);

	ZeroMemory(buttonStatus, sizeof(byte) * MAX_INPUT_MOUSE);
	ZeroMemory(buttonOldStatus, sizeof(byte) * MAX_INPUT_MOUSE);
	ZeroMemory(buttonMap, sizeof(byte) * MAX_INPUT_MOUSE);

	ZeroMemory(startDbclk, sizeof(DWORD) * MAX_INPUT_MOUSE);
	ZeroMemory(buttonCount, sizeof(int) * MAX_INPUT_MOUSE);

	timeDblclk = GetDoubleClickTime();
	startDbclk[0] = GetTickCount();

	for (int i = 1; i < MAX_INPUT_MOUSE; i++)
	{
		startDbclk[i] = startDbclk[0];
	}
}


Mouse::~Mouse()
{
}

Mouse * Mouse::Get()
{
	if (instance == NULL)
	{
		instance = new Mouse;
	}

	return instance;
}

void Mouse::Delete()
{
	SAFE_DELETE(instance);
}

// 비동기 함수 ::실행이 되지만 자체적으로 돌아간다. 
LRESULT CALLBACK Mouse::InputProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_MOUSEWHEEL)
	{
		// short or word
		WORD tWheelValue = HIWORD(wParam);

		wheelOldStatus.z = wheelStatus.z;
		wheelStatus.z = (float)tWheelValue;
	}

	return TRUE;
}

void Mouse::Update()
{
	POINT ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(desc.Handle, &ptMouse);

	//position.x = (ptMouse.x / desc.Width) * 2 -1;
	position.x = ptMouse.x;
	position.y = desc.Height - ptMouse.y;

	memcpy(buttonOldStatus, buttonStatus, sizeof(buttonOldStatus));


	ZeroMemory(buttonStatus, sizeof(buttonStatus));
	ZeroMemory(buttonMap, sizeof(buttonMap));

	buttonStatus[0] = GetAsyncKeyState(VK_LBUTTON) & 0x8000 ? 1 : 0;
	buttonStatus[1] = GetAsyncKeyState(VK_RBUTTON) & 0x8000 ? 1 : 0;
	buttonStatus[2] = GetAsyncKeyState(VK_MBUTTON) & 0x8000 ? 1 : 0;

	for (int i = 0; i < MAX_INPUT_MOUSE; i++)
	{
		int tOldStatus = buttonOldStatus[i];
		int tStatus = buttonStatus[i];

		if (tOldStatus == 0 && tStatus == 1)
		{
			buttonMap[i] = (byte)InputStatus::DOWN;
		}
		else if (tOldStatus == 1 && tStatus == 0)
		{
			buttonMap[i] = (byte)InputStatus::UP;
		}
		else if (tOldStatus == 1 && tStatus == 1)
		{
			buttonMap[i] = (byte)InputStatus::PRESS;
		}
		else
		{
			buttonMap[i] = (byte)InputStatus::NONE;
		}
	}

	DWORD tButtonStatus = GetTickCount();

	for (DWORD i = 0; i < MAX_INPUT_MOUSE; i++)
	{
		if (buttonMap[i] == (byte)InputStatus::DOWN)
		{
			if (buttonCount[i] == 1)
			{
				if ((tButtonStatus - startDbclk[i]) >= timeDblclk)
				{
					buttonCount[i] = 0;
				}
				buttonCount[i]++;

				if (buttonCount[i] == 1)
				{
					startDbclk[i] = tButtonStatus;
				}
			}

		}

		if (buttonMap[i] == (byte)InputStatus::UP)
		{
			if (buttonCount[i] == 1)
			{
				if ((tButtonStatus - startDbclk[i]) >= timeDblclk)
				{
					buttonCount[i] = 0;
				}
			}
			else if (buttonCount[i] == 2)
			{
				if ((tButtonStatus - startDbclk[i]) <= timeDblclk)
				{
					buttonMap[i] = (byte)InputStatus::DBLCLK;
				}

				buttonCount[i] = 0;
			}
		}
	}

	// Wheel : 2D에서만 아래 처럼 가능 
	//wheelMoveValue = wheelStatus - wheelOldStatus;
	position.z = wheelStatus.z - wheelOldStatus.z;
}
