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
	float m_fRadianX = 0.0f;
	float m_fRadianY = 0.0f;
	bool m_bDrag = false;
	DWORD m_dwKeyState[256];
	POINT m_ptMouse;
	DWORD m_dwMouseState[3];
	POINT m_ptMouseClick;
	POINT m_ptDeltaMouse;
public:
	DWORD	GetKey(DWORD dwKey);
	T::TVector2 GetDelta();
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
public:
	JInput();
	~JInput();


};

