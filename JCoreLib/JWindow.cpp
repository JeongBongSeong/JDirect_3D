#include "JWindow.h"
//LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
RECT g_rtClient;
HWND g_hWnd;
JWindow* g_pWindow = nullptr;
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_SIZE:
	{
		UINT iWidth = LOWORD(lParam);
		UINT iHeight = HIWORD(lParam);
		g_pWindow->ResizeDevice(iWidth, iHeight);
	}break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);// WM_QUIT
	}break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}
void     JWindow::ResizeDevice(UINT iWidth, UINT iHeight)
{
}

LRESULT  JWindow::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return 0;
}

// 1. 윈도우 클래스 등록, 허가(OS)
WORD JWindow::MyRegisterClass(HINSTANCE hInstance)
{
	m_hInstance = hInstance;
	WNDCLASSW wc;
	ZeroMemory(&wc, sizeof(WNDCLASSW));
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = L"JBS";

	if (RegisterClass(&wc) == false)
	{
		return FALSE;
	}
	
	return TRUE;
}

// 2. 윈도우 생성
BOOL JWindow::SetWindow(const WCHAR* szTitle, int iWidth,int iHeight)
{
	RECT rt;
	rt = { 0,0,iWidth,iHeight };

	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, FALSE);
	//
	m_hWnd = CreateWindow(
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
	if (m_hWnd == NULL)
	{
		return false;
	}
	//
	g_hWnd = m_hWnd;
	
	//클라이언트에 대한 영역을 가져온다. 타이틀바와 좌우 하단의 베젤을 제외한 오직 화면의 크기
	GetClientRect(m_hWnd, &m_rtClient);
	
	//Window에 대한 영역을 가져온다. (인자값에 해당하는 값) 
	GetWindowRect(m_hWnd, &m_rtWindow);
	g_rtClient = m_rtClient;

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
JWindow::JWindow()
{
	g_pWindow = this;
}

JWindow::~JWindow()
{

}
