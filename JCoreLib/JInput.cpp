#include "JInput.h"

POINT g_ptMouse;

DWORD	JInput::GetKey(DWORD dwKey)
{
	return m_dwKeyState[dwKey];
}

bool	JInput::Init()
{
	ZeroMemory(&m_dwKeyState, sizeof(DWORD) * 256);
	return true;
}

bool	JInput::Frame()
{
	POINT ptOffset = g_ptMouse;
	//화면(스크린)좌표계
	GetCursorPos(&m_ptMouse);


	//클라이언트(윈도우)좌표계
	ScreenToClient(g_hWnd, &m_ptMouse);
	g_ptMouse = m_ptMouse;
	if (m_ptMouse.x < 0 || m_ptMouse.x > g_rtClient.right ||
		m_ptMouse.y < 0 || m_ptMouse.y > g_rtClient.bottom)
	{
		m_bDrag = false;
	}

	// 마우스 버튼 VK_LBUTTON, VK_RBUTTON, VK_MBUTTON,
	for (int iKey = 0; iKey < 256; iKey++)
	{
		SHORT sKey = GetAsyncKeyState(iKey);
		if (sKey & 0x8000)
		{
			if (m_dwKeyState[iKey] == KEY_FREE)
			{
				m_dwKeyState[iKey] = KEY_PUSH;
			}
			else
			{
				m_dwKeyState[iKey] = KEY_HOLD;
			}
		}
		else // 안 눌러 졌다면
		{
			if (m_dwKeyState[iKey] == KEY_PUSH || m_dwKeyState[iKey] == KEY_HOLD)
			{
				m_dwKeyState[iKey] = KEY_UP;
			}
			else
			{
				m_dwKeyState[iKey] = KEY_FREE;
			}
		}

	}
	m_dwMouseState[0] = m_dwKeyState[VK_LBUTTON];
	m_dwMouseState[1] = m_dwKeyState[VK_RBUTTON];
	m_dwMouseState[2] = m_dwKeyState[VK_MBUTTON];


	if (m_dwMouseState[0] == KEY_PUSH)
	{
		m_bDrag = true;
		m_ptMouseClick = m_ptMouse;
	}

	if (m_dwMouseState[0] == KEY_UP)
	{
		m_bDrag = false;
	}
	if (m_bDrag)
	{
		m_ptDeltaMouse.x = ptOffset.x - m_ptMouse.x;
		m_ptDeltaMouse.y = ptOffset.y - m_ptMouse.y;
	}
	return true;
}

bool	JInput::Render()
{ 
	return true;
}

bool	JInput::Release()
{
	return true;
}

JInput::JInput()
{
	m_ptDeltaMouse.x = 0.0f;
	m_ptDeltaMouse.y = 0.0f;
}

JInput::~JInput()
{
}
