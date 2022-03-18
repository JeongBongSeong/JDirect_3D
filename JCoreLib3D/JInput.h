#pragma once
#include"JStd.h"

enum KeyState
{
	KEY_FREE = 0,	//기본상태
	KEY_UP,			//누른거 올라옴
	KEY_PUSH,		//누름
	KEY_HOLD,		//눌러진상태유지
};

class JInput : public JSingleton<JInput>
{
public:
	DWORD m_dwKeyState[256];
	POINT m_ptMouse;
	DWORD m_dwMouseState[3];
public:
	DWORD	GetKey(DWORD dwKey);
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
public:
	JInput();
	~JInput();


};

