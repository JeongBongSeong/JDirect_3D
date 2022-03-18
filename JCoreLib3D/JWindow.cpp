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

// 1. ������ Ŭ���� ���, �㰡(OS)
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

// 2. ������ ����
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
	
	//Ŭ���̾�Ʈ�� ���� ������ �����´�. Ÿ��Ʋ�ٿ� �¿� �ϴ��� ������ ������ ���� ȭ���� ũ��
	GetClientRect(m_hWnd, &m_rtClient);
	
	//Window�� ���� ������ �����´�. (���ڰ��� �ش��ϴ� ��) 
	GetWindowRect(m_hWnd, &m_rtWindow);
	g_rtClient = m_rtClient;

	ShowWindow(m_hWnd, SW_SHOW);

	return true;
}

bool JWindow::WinRun()
{
	MSG msg;

	
	//�޼��� ť�� �޼����� ������ ���(��ȯ����)
	//if (GetMessage(&msg, nullptr, 0, 0)==FALSE) // �̰��� ���� ��ȯ���̾�� else�� ������ �� ����
	//
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			return false;
		}
		TranslateMessage(&msg);	// �޼��� ����
		DispatchMessage(&msg);	// ���������ν��� ȣ��
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
