#include "JWindow.h"
//LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

// 1. 윈도우 클래스 등록, 허가(OS)
WORD JWindow::MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSW wc;
	ZeroMemory(&wc, sizeof(WNDCLASSW));
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = L"JBS";
	wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);

	if (RegisterClass(&wc) == false)
	{
		return FALSE;
	}
	m_hInstance = hInstance;

	return TRUE;
}

// 2. 윈도우 생성
BOOL JWindow::SetWindow(const WCHAR* szTitle, int iWidth,int iHeight)
{
	RECT rt;
	rt = { 0,0,iWidth,iHeight };

	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, FALSE);
	//
	HWND hWnd = CreateWindow(
		L"JBS",
		szTitle,
		WS_OVERLAPPEDWINDOW,
		210,
		140,
		rt.right-rt.left,
		rt.bottom-rt.top,
		NULL,
		NULL,
		m_hInstance,
		NULL);
	
	//
	m_hWnd = hWnd;

	//
	if (hWnd == NULL)
	{
		return false;
	}
	
	//클라이언트에 대한 영역을 가져온다. 타이틀바와 좌우 하단의 베젤을 제외한 오직 화면의 크기
	GetClientRect(m_hWnd, &m_rtClient);
	
	//Window에 대한 영역을 가져온다. (인자값에 해당하는 값) 
	GetWindowRect(m_hWnd, &m_rtWindow);

	ShowWindow(m_hWnd, SW_SHOW);

	return true;
}

bool JWindow::WinRun()
{
	MSG msg;

	
	//메세지 큐에 메세지가 없으면 블록(반환안함)
	//if (GetMessage(&msg, nullptr, 0, 0)==FALSE) // 이것을 사용시 반환값이없어서 else를 실행할 수 없음
	//
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			return false;
		}
		TranslateMessage(&msg);	// 메세지 번역
		DispatchMessage(&msg);	// 윈도우프로시져 호출
	}

	return true;
}
