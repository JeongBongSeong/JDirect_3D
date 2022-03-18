#include "JThread.h"
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
unsigned int __stdcall JThread::Runner(LPVOID param)
{
	JThread* pThread = (JThread*)param;
	if (pThread != nullptr)
	{
		pThread->Run();
	}
	return 0;
}

void JThread::Create()
{
	if (m_bStarted != false) return;
	m_hThread = _beginthreadex(nullptr, 0, Runner, this, 0, &m_iID);
	m_bStarted = true;
}

void JThread::Create(LPVOID pValue)
{
	m_hThread = _beginthreadex(nullptr, 0, Runner, this, 0, &m_iID);
	m_pObject = pValue;
	m_bStarted = true;

}
bool JThread::Run()
{
	return true;
}


