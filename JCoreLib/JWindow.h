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
	BOOL SetWindow(const WCHAR* szTitle = L"Battle City Tank", int iWidth = 1152, int iHeight = 864);
	bool WinRun();
	virtual LRESULT  MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual void     ResizeDevice(UINT iWidth, UINT iHeight);
public:
	JWindow();
	virtual ~JWindow();
};

