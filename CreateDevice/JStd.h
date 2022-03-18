#pragma once
#include<iostream>
#include<vector>
#include<list>
#include<map>
#include<windows.h>
using namespace std;

#define GAME_START int APIENTRY wWinMain(HINSTANCE	hInstance,	HINSTANCE	hPrevInstance,	LPWSTR		lpCmdLine,	int			mCmdShow){	JSample core;	
#define GAME_WIN(s,x,y) if (!core.MyRegisterClass(hInstance))	{		return 1;	}	if (!core.SetWindow(L#s,x,y))	{		return 1;	}	core.GameRun();}
#define SIMPLE_WIN() if (core.SetWinClass(hInstance) == FALSE) return 1;   if (core.SetWindow() == FALSE) return 1;   core.GameRun();    return 1;}
#define GAME_RUN(s,x,y) GAME_START GAME_WIN(s,x,y)
#define RUN() GAME_START; SIMPLE_WIN();