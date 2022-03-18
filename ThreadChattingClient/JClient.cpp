#include "JClient.h"
std::string g_Name;
HANDLE g_hThreadEvent;	
BOOL g_bExit = FALSE;
//HANDLE g_hRecvThread;
int RecvPacketHeader(SOCKET sock, UPACKET& packet)
{
	char szRecvBuffer[256] = { 0, };
	ZeroMemory(&packet, sizeof(UPACKET));
	int iRecvSize = 0;

	do {
		int iRecvByte = recv(sock, szRecvBuffer, PACKET_HEADER_SIZE, 0);
		iRecvSize += iRecvByte;
		if (iRecvByte == 0)
		{
			closesocket(sock);
			std::cout << "recv 정상 종료됨." << std::endl;
			return -1;
		}
		if (iRecvByte == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				closesocket(sock);
				std::cout << "recv 종료됨." << std::endl;
				return -1;
			}
			else
			{
				return 0;
			}
		}
	} while (iRecvSize < PACKET_HEADER_SIZE);

	memcpy(&packet, szRecvBuffer, PACKET_HEADER_SIZE);
	return 1;
}

int RecvPacketData(SOCKET sock, UPACKET& packet)
{
	int iRecvSize = 0;

	do {
		int iRecvByte = recv(sock, packet.msg, packet.ph.len - PACKET_HEADER_SIZE - iRecvSize, 0);
		iRecvSize += iRecvByte;
		if (iRecvByte == 0)
		{
			closesocket(sock);
			std::cout << "recv 정상 종료됨." << std::endl;
			return -1;
		}
		if (iRecvByte == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				closesocket(sock);
				std::cout << "recv 종료됨." << std::endl;
				return -1;
			}
			else
			{
				return 0;
			}
		}
	} while (iRecvSize < packet.ph.len - PACKET_HEADER_SIZE);

	return 1;
}
int SendPacket(SOCKET sock, char* msg, WORD type)
{

	JPacket jPacket(type);
	jPacket << 1 << g_Name.c_str() << msg;

	char* pData = (char*)&jPacket.m_uPacket;
	int iSendSize = 0;
	do {
		int iSendByte = send(sock, &pData[iSendSize], jPacket.m_uPacket.ph.len - iSendSize, 0);
		if (iSendByte == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				return -1;
			}
		}
		iSendSize += iSendByte;

	} while (iSendSize < jPacket.m_uPacket.ph.len);

	return iSendSize;
}

DWORD WINAPI SendThread(LPVOID lpParameter)
{
	SOCKET sock = (SOCKET)lpParameter;
	char szBuffer[256] = { 0, };
	char* csData;
	csData = (char*)"exit\n";
	while (1)
	{
		DWORD ret = WaitForSingleObject(g_hThreadEvent, INFINITE);
		if (ret != WAIT_OBJECT_0)
		{
			break;
		}
		ZeroMemory(szBuffer, sizeof(char) * 256);
		Sleep(100);
		
		fgets(szBuffer, 256, stdin);
		
		
		if (strcmp(szBuffer, csData)==0)
		{
			g_bExit = TRUE;
			Sleep(1000);
		}
		if (strlen(szBuffer) == 0)
		{
			std::cout << "send 정상 종료됨" << std::endl;
			break;
		}

		int iSendSize = SendPacket(sock, szBuffer, PACKET_CHAT_MSG);
		if (iSendSize < 0)
		{
			std::cout << "send 종료됨" << std::endl;
			break;
		}
	}
	return 0;
}

DWORD WINAPI RecvThread(LPVOID lpParameter)
{
	SOCKET sock = (SOCKET)lpParameter;
	char szBuffer[256] = { 0, };
	while (1)
	{
		DWORD ret = WaitForSingleObject(g_hThreadEvent, INFINITE);
		if (ret != WAIT_OBJECT_0)
		{
			break;
		}
		UPACKET uPacket;
		int iRet = RecvPacketHeader(sock, uPacket);
		if (iRet < 0) continue;
		if (iRet == 1)
		{

			int iRet = RecvPacketData(sock, uPacket);
			if (iRet < 0) break;
			if (iRet == 0) continue;
			JPacket data;
			data.m_uPacket = uPacket;
			JChatMsg recvdata;
			ZeroMemory(&recvdata, sizeof(JChatMsg));
			data >> recvdata.index >> recvdata.name >> recvdata.msg;
			std::cout << "\n" << "[" << recvdata.name << "] : " << recvdata.msg;
		}
	}
	return 0;

}

void JClient::InitClient()
{
	g_hThreadEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	//g_hRecvThread = CreateEvent(NULL, TRUE, FALSE, NULL);
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return;
	}
	m_Sock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(SOCKADDR_IN));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(10000);
	sa.sin_addr.s_addr = inet_addr("127.0.0.1");
	//std::cout << "이름 : ";
	//std::cin >> g_Name;


	int ret = connect(m_Sock, (sockaddr*)&sa, sizeof(sa));
	if (ret == SOCKET_ERROR)
	{
		return;
	}
	std::cout << "사용자 이름 : ";
	getline(std::cin,g_Name);
	std::cout << g_Name << "님 접속 성공" << std::endl;

}

void JClient::Run()
{
	m_hSendThread = ::CreateThread(NULL, NULL, SendThread, (LPVOID)m_Sock, 0, &m_hSendThreadID);

	m_hRecvThread = ::CreateThread(NULL, NULL, RecvThread, (LPVOID)m_Sock, 0, &m_hRecvThreadID);

	u_long on = 1;
	ioctlsocket(m_Sock, FIONBIO, &on);

	SetEvent(g_hThreadEvent);
	while (!g_bExit)
	{
		Sleep(1);
		//ResetEvent(g_hConnectEvent);
	}
	std::cout << "접속종료" << std::endl;

}
void JClient::Release()
{
	CloseHandle(m_hSendThread);
	closesocket(m_Sock);
	WSACleanup();
	CloseHandle(g_hThreadEvent);
}
JClient::~JClient()
{
}