#include "JServerObj.h"

JServerObj::JServerObj()
{
	InitializeCriticalSection(&m_cs);
	m_hKillEvent = ::CreateEvent(0, TRUE, FALSE, 0);
}

JServerObj::~JServerObj()
{
	DeleteCriticalSection(&m_cs);
	CloseHandle(m_hKillEvent);
}
