#pragma once

#define _WINSOCKAPI_
#include <windows.h>
#include <winsock2.h>

#include <vector>
#include <list>
#include <iostream>
#pragma comment	(lib, "ws2_32.lib")
#pragma comment	(lib, "winmm.lib")
#ifdef _DEBUG
#pragma comment	(lib, "JCoreNetwork.lib")
#else
#pragma comment	(lib, "JCoreNetwork.lib")
#endif
using namespace std;