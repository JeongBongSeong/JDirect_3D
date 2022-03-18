#pragma once
#include"JStd.h"
class JServerObj
{
public:
	CRITICAL_SECTION	m_cs;
	HANDLE				m_hKillEvent;
public:
	JServerObj();
	virtual ~JServerObj();
};

