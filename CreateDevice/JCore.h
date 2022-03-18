#pragma once
#include"JWindow.h"
class JCore : public JWindow
{
public:
	//게임 반복 전 실행
	bool CoreInit();

	// 게임 실행 반복
	bool GameRun();
		bool CoreFrame();
		bool CoreRender();

	//게임 반복 종료 후 실행
	bool CoreRelease();

	//
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
	
};

