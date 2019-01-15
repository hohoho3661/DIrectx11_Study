#pragma once
#include "./Program.h"
class Window
{
private:
	static LRESULT CALLBACK WndProc(
		HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
	Program* game;
public:
	Window();
	~Window();

	WPARAM Run();
};

