#pragma once
#include"JCore.h"
#include "JAsyncSelect.h"
#include "JDxObject.h"
#include "DDSTextureLoader.h"
#include "WICTextureLoader.h"

class Sample : public JCore
{
public:
	ID3D11ShaderResourceView* m_pSRV0;
	ID3D11Resource* m_pTexture0;
	ID3D11ShaderResourceView* m_pSRV1;
	ID3D11Resource* m_pTexture1;
	ID3D11BlendState* m_pAlphaBlend;

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

