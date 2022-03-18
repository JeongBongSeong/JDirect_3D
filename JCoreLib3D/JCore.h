#pragma once
#include"JDevice.h"
#include"JDxObject.h"
#include"JInput.h"
#include"JTImer.h"
#include "JWriteFont.h"

class JCore : public JDevice
{
public:
	JTimer m_GameTimer;
	JWriteFont m_dxWrite;
	float m_fColor[4];
public:
	//���� �ݺ� �� ����
	bool CoreInit();

	// ���� ���� �ݺ�
	bool GameRun();
		bool CoreFrame();
		bool CoreRender();

	//���� �ݺ� ���� �� ����
	bool CoreRelease();

	//
public:
	virtual void	CreateResizeDevice(UINT iWidth, UINT iHeight) {};
	virtual void	DeleteResizeDevice(UINT iWidth, UINT iHeight) {};
	void			ResizeDevice(UINT iWidth, UINT iHeight);
public:
	virtual bool	Init() { return true; };
	virtual bool	Frame() { return true; };
	virtual bool	Render() { return true; };
	virtual bool	Release() { return true; };
public:
	JCore();
	virtual ~JCore();
};

