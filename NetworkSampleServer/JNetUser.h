#pragma once
#include "JNetStd.h"
class JNetUser
{
public:
	JNetUser();
	JNetUser(SOCKET sock, SOCKADDR_IN addr);
	virtual ~JNetUser();
};

