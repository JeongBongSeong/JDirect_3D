#include "JLobbyServer.h"

DWORD WINAPI WorkerThread(LPVOID param)
{
	JLobbyServer* pServer = (JLobbyServer*)param;
	DWORD dwTransfer;
	ULONG_PTR KeyValue;
	OVERLAPPED* pOverlapped;
	while (1)
	{
		if (WaitForSingleObject(pServer->m_hKillEvent, 1) == WAIT_OBJECT_0)
		{
			break;
		}

		BOOL bReturn = ::GetQueuedCompletionStatus(pServer->m_hIOCP, &dwTransfer, &KeyValue, &pOverlapped, 1);

		JChatUser* pUser = (JChatUser*)KeyValue;
		JOV* pOV = (JOV*)pOverlapped;
		if (bReturn == TRUE && pUser && pOV)
		{
			if (dwTransfer == 0 && pOV->type == 1000)
			{
				pUser->m_bConnect = false;
			}
			else
			{
				pUser->Dispatch(dwTransfer, pOV);
			}
		}
		else
		{
			if (GetLastError() != WAIT_TIMEOUT)
			{
				::SetEvent(pServer->m_hKillEvent);
				break;
			}
		}
		
	}
	return 1;
}

JLobbyServer::JLobbyServer()
{
}

JLobbyServer::~JLobbyServer()
{
}
bool JLobbyServer::InitServer(int iPort)
{
	JServer::InitServer(iPort);
	m_hIOCP = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
	for (int iThread = 0; iThread < MAX_WORKER_THREAD; iThread++)
	{
		DWORD id;
		m_hWorkThread[iThread] = ::CreateThread(0, 0, WorkerThread, this, 0, &id);
	}
	return true;
}

// 자세히 다시보자
bool JLobbyServer::Run()
{
	while (1)
	{
		EnterCriticalSection(&m_cs);
		for (JNetUser* tUser : m_Userlist)
		{
			JChatUser* pChat = (JChatUser*)tUser;
			if (pChat->m_packetPool.size() > 0)
			{
				Broadcast(tUser);
			}
		}
		list<JNetUser*>::iterator iter;
		for (iter = m_Userlist.begin();
			iter != m_Userlist.end();)
		{
			if ((*iter)->m_bConnect == false)
			{
				(*iter)->DisConnect();
				delete (*iter);
				iter = m_Userlist.erase(iter);
			}
			else
			{
				iter++;
			}
		}

		LeaveCriticalSection(&m_cs);
		Sleep(1);
	}
	return true;

}

bool JLobbyServer::Release()
{
	CloseHandle(m_hIOCP);
	JServer::Release();
	return false;
}

bool JLobbyServer::AddUser(SOCKET sock, SOCKADDR_IN clientAddr)
{
	JChatUser* user = new JChatUser;
	user->set(sock, clientAddr);

	//논블럭킹 선언  ( Client 소켓 )
	u_long on = 1;
	ioctlsocket(sock, FIONBIO, &on);
	//
	
	EnterCriticalSection(&m_cs);
		m_Userlist.push_back(user);
	LeaveCriticalSection(&m_cs);
	
	::CreateIoCompletionPort((HANDLE)sock, m_hIOCP, (ULONG_PTR)user, 0);
	user->Recv();

	char ip[INET_ADDRSTRLEN];
	cout <<
		"ip = " << inet_ntop(AF_INET,&(clientAddr.sin_addr),ip,INET6_ADDRSTRLEN) << endl <<
		"port = " << ntohs(clientAddr.sin_port) << endl <<
		" " << endl;


	return true;
}