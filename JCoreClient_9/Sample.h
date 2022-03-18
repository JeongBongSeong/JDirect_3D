#pragma once
#include"JCore.h"
#include "JAsyncSelect.h"
#include "JPlayerObj2D.h"
#include "JObjectNpc2D.h"
#include "JSoundMgr.h"
#include "JIntroWorld.h"
#include "JLoginWorld.h"
#include "JZoneWorld.h"

class Sample : public JCore
{
public:
	JIntroWorld m_IntroWorld;
	//JLoginWorld m_LoginWorld;
	JZoneWorld m_ZoneWorld;
public:
	JAsyncSelect		m_Net;
	HWND				m_hEdit;
	HWND				m_hButton;
	HWND				m_hListBox;
	int					m_iChatCnt;
public:
	JInput m_Input;
public:
	virtual void	CreateResizeDevice(UINT iWidth, UINT iHeight) override;
	virtual void	DeleteResizeDevice(UINT iWidth, UINT iHeight) override;

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

