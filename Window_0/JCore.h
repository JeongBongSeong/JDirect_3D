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


};

