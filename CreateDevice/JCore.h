#pragma once
#include"JWindow.h"
class JCore : public JWindow
{
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
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
	
};

