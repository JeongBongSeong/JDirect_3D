#pragma once
#include"JCore.h"
#include "JAsyncSelect.h"
#include "JPlayerObj2D.h"
#include "JObjectNpc2D.h"
class Sample : public JCore
{
public:
	JInput m_Input;

public:
	JAsyncSelect		m_Net;
	HWND				m_hEdit;
	HWND				m_hButton;
	HWND				m_hListBox;
	int					m_iChatCnt;

public:
	JPlayerObj2D		m_PlayerObj;
public:
	vector<JObjectNpc2D*> m_NpcLlist;
public:
	virtual bool	Init()  override;
	virtual bool	Frame()  override;
	virtual bool	Render()  override;
	virtual bool	Release()  override;
	virtual LRESULT  MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
public:
	Sample();
	~Sample();
};

