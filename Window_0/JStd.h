#pragma once
#include<iostream>
#include<vector>
#include<list>
#include<map>
#include<windows.h>
using namespace std;

#define GAME_START int APIENTRY wWinMain(HINSTANCE	hInstance,	HINSTANCE	hPrevInstance,	LPWSTR		lpCmdLine,	int			mCmdShow){	JSample Win;	
#define GAME_WIN(s,x,y) if (!Win.MyRegisterClass(hInstance))	{		return 1;	}	if (!Win.SetWindow(L#s,x,y))	{		return 1;	}	Win.GameRun();}
#define GAME_RUN(s,x,y) GAME_START GAME_WIN(s,x,y)