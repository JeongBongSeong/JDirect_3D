#include "JAccepter.h"

JAccepter::JAccepter(SOCKADDR_IN& sa)
{
	m_Sa = sa;
}

int JAccepter::Join()
{
	if (WSAStartup(MAKEWORD(2, 2), &m_Wsa) != 0)
	{
		return WSA_ERROR;
	}
	m_ListenSock = socket(AF_INET, SOCK_STREAM, 0);	//���� ������ ����
	ZeroMemory(&m_Sa, sizeof(SOCKADDR_IN));

	m_Sa.sin_family = AF_INET;		//TCP
	m_Sa.sin_port = htons(m_iPort);			//port ��ȣ
	m_Sa.sin_addr.s_addr = htonl(INADDR_ANY); // �� ��ǻ�ͷ� ������ IP�� �޾�(INADDR_ANY)  //inet_addr("192.168.0.12");	//���ڿ��� 4����Ʈ�� ��ȯ�ؼ� �����ϴ� ��	�� IP

	int iRet = bind(m_ListenSock, (sockaddr*)&m_Sa, sizeof(SOCKADDR_IN));	//���ϰ� ������ ���ε�
	if (iRet == SOCKET_ERROR) return SOCKET_ERROR;

	iRet = listen(m_ListenSock, SOMAXCONN);		// ������ �����Ѵ�.
	if (iRet == SOCKET_ERROR) return SOCKET_ERROR;
	
	m_iLen = sizeof(m_ClientAddr);

	//���ŷ ����  ( Listen ����)
	u_long on = 1;
	ioctlsocket(m_ListenSock, FIONBIO, &on);
	return true;
}

int JAccepter::Run()
{
	m_ClientSock = accept(m_ListenSock, (sockaddr*)&m_ClientAddr, &m_iLen);	// accept�� �̿��Ͽ� ���� ������ Ȯ���Ѵ�. ������ ����ŷ���� �����߱⿡ ���� �޾� �ٷγѾ ���ŷ�� ��� ����Ѵ�.

	if (m_ClientSock == SOCKET_ERROR)	//���� ������ ��� (-1)
	{
		int iError = WSAGetLastError();
		//std::cout << "ErrorCode : " << iError << std::endl;
		//�Ʒ� WSA E WOULD BLOCK �� ���� ��û�� ���� ���� ��� ������ ���� 
		if (iError != WSAEWOULDBLOCK)	//���� ���� (���ú� �Լ��� ������ ��)	WSA E WOULD BLOCK // �� ������ �߸� ���� // �ƴϸ� ������ ��
		{
			std::cout << "ErrorCode=" << iError << std::endl;
			return false;
		}

	}
	else
	{
		JNetUser user;
		user.set(m_ClientSock, m_ClientAddr);
		m_Userlist.push_back(user);

		std::cout <<
			"ip = " << inet_ntoa(m_ClientAddr.sin_addr) << std::endl <<
			"port = " << ntohs(m_ClientAddr.sin_port) << std::endl <<
			" " << std::endl;

		//���ŷ ����  ( Client ���� )
		u_long on = 1;
		ioctlsocket(m_ClientSock, FIONBIO, &on);

		std::cout << m_Userlist.size() << " �� ������.." << std::endl;

	}
}