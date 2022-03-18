#pragma once
#include"JStd.h"
class JWindow
{
public:
	HINSTANCE m_hInstance;
	HWND m_hWnd;
	RECT m_rtClient;
	RECT m_rtWindow;
public:
	WORD MyRegisterClass(HINSTANCE hInstance);
	BOOL SetWindow(const WCHAR* szTitle = L"Defalut", int iWidth = 800, int iHeight = 600);
	bool WinRun();
};

