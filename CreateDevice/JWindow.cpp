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

// 1. ������ Ŭ���� ���, �㰡(OS)
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

// 2. ������ ����
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
	
	//Ŭ���̾�Ʈ�� ���� ������ �����´�. Ÿ��Ʋ�ٿ� �¿� �ϴ��� ������ ������ ���� ȭ���� ũ��
	GetClientRect(m_hWnd, &m_rtClient);
	
	//Window�� ���� ������ �����´�. (���ڰ��� �ش��ϴ� ��) 
	GetWindowRect(m_hWnd, &m_rtWindow);

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
