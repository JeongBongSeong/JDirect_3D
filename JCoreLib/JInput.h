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

