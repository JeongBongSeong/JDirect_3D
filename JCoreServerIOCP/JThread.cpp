#include "JThread.h"

void JThread::Create()
{
	if (m_bStarted != false) return;
	m_hThread = _beginthreadex(nullptr, 0, Runner, this, 0, &m_iID );
	m_bStarted = true;
}

void JThread::Create(LPVOID pValue)
{
	if (m_bStarted != false) return;
	m_hThread = _beginthreadex(nullptr, 0, Runner, this, 0, &m_iID);
	m_pObject = pValue;
	m_bStarted = true;

}

void JThread::Join()
{
	::WaitForSingleObject((HANDLE)m_hThread, INFINITE);
}

void JThread::Detach()
{
	CloseHandle((HANDLE)m_hThread);
}

bool JThread::Run()
{
	return false;
}

unsigned int __stdcall JThread::Runner(LPVOID param)
{
	JThread* pThread = (JThread*)param;
	if (pThread != nullptr)
	{
		pThread->Run();
	}
	return 0;
}

JThread::JThread()
{
	m_bStarted = false;
	m_pObject = nullptr;
}

JThread::JThread(LPVOID pValue)
{
	m_bStarted = false;
	m_pObject = nullptr;
	Create(pValue);

}

JThread::~JThread()
{
	CloseHandle((HANDLE)m_hThread);
}
