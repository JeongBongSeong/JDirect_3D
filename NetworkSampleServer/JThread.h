#pragma once
#include"JNetStd.h"
class JThread
{
public:
	uintptr_t m_hThread;
	unsigned int m_iID;
	bool		m_bStarted;
	LPVOID m_pObject;
public:
	JThread();
	JThread(LPVOID pValue);
	virtual ~JThread();
public:
	void Create();
	void Create(LPVOID pValue);
	virtual bool Run();
	static unsigned int __stdcall Runner(LPVOID param);
};

