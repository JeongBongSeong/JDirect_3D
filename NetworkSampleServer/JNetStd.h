#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<winsock2.h>
#include<windows.h>
#include<ws2tcpip.h> // inet_ntop
#include<iostream>
#include<list>
#include<map>
#include<string>
#include<vector>
#include <process.h>
#pragma comment (lib, "ws2_32.lib")

//#pragma comment	(lib, "JCoreServer_r.lib")
using namespace std;
#define MAX_WORKER_THREAD 1
//#define SOCKET_NOT_RECV 0
#define WSA_ERROR -1
//#define SOCKET_RECV_ERROR -3