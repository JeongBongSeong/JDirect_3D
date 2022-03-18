#pragma once
#include "JServerObj.h"
#include <process.h>
class JThread : public JServerObj
{
public:
	uintptr_t m_hThread;
	unsigned int m_iID;
	bool		m_bStarted;
	LPVOID m_pObject;
public:
	void Create();
	void Create(LPVOID pValue);
	void Join();
	void Detach();
	virtual bool Run();
	static unsigned int WINAPI Runner(LPVOID param);
public:
	JThread();
	JThread(LPVOID pValue);
	virtual ~JThread();

};

