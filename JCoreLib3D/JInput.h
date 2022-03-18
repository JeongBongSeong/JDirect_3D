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

