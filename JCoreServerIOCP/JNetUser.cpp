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
		(LPWSAOVERLAPPED)&m_ovRecv,		//구조체변수의 주소값
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
	//현재위치에서 2048보다 크면 0번으로 이동 즉 여러번 
	if (m_iWritePos + iRecvByte >= 2048)
	{
		if (m_iReadPos > 0)
		{
			memmove(&m_szRecvBuffer[0], &m_szRecvBuffer[m_iPacketPos], m_iReadPos);
		}
		m_iPacketPos = 0;
		m_iWritePos = m_iReadPos;
	}
	
	// m_szRecvBuffer에 m_iWritePos 위치시작으로 szRecvBuffer를 iRecvByte만큼 복사
	memcpy(&m_szRecvBuffer[m_iWritePos], szRecvBuffer, iRecvByte);
	
	//쓰기 위치를 받아온 데이터의 사이즈만큼 추가
	m_iWritePos += iRecvByte;

	//읽기 위치를 받아온 데이터의 사이즈만큼 추가
	m_iReadPos += iRecvByte;

	// m_iReadPos의 크기가 헤더사이즈보다 크거나 같으면 읽을 데이터가 존재한다는 것
	if (m_iReadPos >= PACKET_HEADER_SIZE)
	{
		//가져온 패킷을 다넣으면 UPACKET 형태로 각각의 값이 적용되어 들어간다.
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