#include"JNetUser.h"

int JNetUser::Recv()
{
	m_wsaRecvBuffer.len = sizeof(char) * 256;
	m_wsaRecvBuffer.buf = m_szRecv;
	m_ovRecv.type = 1000;

	DWORD dwRead;
	DWORD lpFlags = 0;
	BOOL ret = WSARecv(m_Sock,
		&m_wsaRecvBuffer,
		1, &dwRead,&lpFlags,
		(LPWSAOVERLAPPED)&m_ovRecv,		//����ü������ �ּҰ�
		NULL);
	
	return 0;
}

void JNetUser::set(SOCKET sock, SOCKADDR_IN sockaddr)//,string,short)
{
	m_bConnect = true;
	ZeroMemory(m_szRecvBuffer, sizeof(char) * 2048);
	m_iPacketPos = 0;
	m_iWritePos = 0;
	m_iReadPos = 0;
	//int m_iWritePos;
	//int m_iReadPos;

	m_Sock = sock;
	m_Addr = sockaddr;
	m_csName = inet_ntoa(m_Addr.sin_addr);
	m_iPort = ntohs(m_Addr.sin_port);
}
bool JNetUser::DisConnect()
{
	closesocket(m_Sock);
	return true;
}
int JNetUser::Dispatch(DWORD dwTrans, JOV* tov)
{
	if (m_bConnect == false)
	{
		return 0;
	}
	if (tov->type == 1000)
	{
		if (!DispatchRecv(m_szRecv, dwTrans))
		{
		}
		Recv();
	}
	if (tov->type == 2000)
	{
		if (!DispatchSend(dwTrans))
		{
		}
	}
	return 1;
}
int JNetUser::DispatchSend(DWORD dwTrans)
{
	return 0;
}
JNetUser::JNetUser()
{
}
JNetUser::~JNetUser()
{
}
int JNetUser::DispatchRecv(char* szRecvBuffer, int iRecvByte)
{
	//������ġ���� 2048���� ũ�� 0������ �̵� �� ������ 
	if (m_iWritePos + iRecvByte >= 2048)
	{
		if (m_iReadPos > 0)
		{
			memmove(&m_szRecvBuffer[0], &m_szRecvBuffer[m_iPacketPos], m_iReadPos);
		}
		m_iPacketPos = 0;
		m_iWritePos = m_iReadPos;
	}
	
	// m_szRecvBuffer�� m_iWritePos ��ġ�������� szRecvBuffer�� iRecvByte��ŭ ����
	memcpy(&m_szRecvBuffer[m_iWritePos], szRecvBuffer, iRecvByte);
	
	//���� ��ġ�� �޾ƿ� �������� �����ŭ �߰�
	m_iWritePos += iRecvByte;

	//�б� ��ġ�� �޾ƿ� �������� �����ŭ �߰�
	m_iReadPos += iRecvByte;

	// m_iReadPos�� ũ�Ⱑ ���������� ũ�ų� ������ ���� �����Ͱ� �����Ѵٴ� ��
	if (m_iReadPos >= PACKET_HEADER_SIZE)
	{
		//������ ��Ŷ�� �ٳ����� UPACKET ���·� ������ ���� ����Ǿ� ����.
		UPACKET* pPacket = (UPACKET*)&m_szRecvBuffer[m_iPacketPos];
		if(pPacket->ph.len <= m_iReadPos)
		{
			do {
				JPacket jPacket(pPacket->ph.type);
				memcpy(&jPacket.m_uPacket, &m_szRecvBuffer[m_iPacketPos], pPacket->ph.len);
				m_packetPool.push_back(jPacket);

				m_iPacketPos += pPacket->ph.len;
				m_iReadPos -= pPacket->ph.len;
				if (m_iReadPos < PACKET_HEADER_SIZE)
				{
					break;
				}
				pPacket = (UPACKET*)&m_szRecvBuffer[m_iPacketPos];
			} while (pPacket->ph.len <= m_iReadPos);
		}
	}
	

	return 1;
}