#pragma once
#pragma comment(lib,"JCoreLib.lib")
#include "JDxObject.h"
#include"JCore.h"
#include "JAsyncSelect.h"

class Sample : public JCore
{
public:
	JAsyncSelect		m_Net;
	HWND				m_hEdit;
	HWND				m_hButton;
	HWND				m_hListBox;
	int					m_iChatCnt;

public:
	vector<JDxObject> m_ObjectList;
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

