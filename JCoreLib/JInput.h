#pragma once
#include"JStd.h"

enum KeyState
{
	KEY_FREE = 0,	//�⺻����
	KEY_UP,			//������ �ö��
	KEY_PUSH,		//����
	KEY_HOLD,		//��������������
};

class JInput : public JSingleton<JInput>
{
public:
	bool m_bDrag = false;
	DWORD m_dwKeyState[256];
	POINT m_ptMouse;
	DWORD m_dwMouseState[3];
	POINT m_ptMouseClick;
	POINT m_ptDeltaMouse;
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

