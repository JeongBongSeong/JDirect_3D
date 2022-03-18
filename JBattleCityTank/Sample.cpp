//위치46 62  크기67 78
#include "Sample.h"
#include "JObjectMgr.h"


void	Sample::CreateResizeDevice(UINT iWidth, UINT iHeight)
{
	int k = 0;
}
void	Sample::DeleteResizeDevice(UINT iWidth, UINT iHeight)
{
	int k = 0;
}
LRESULT  Sample::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case 200:
		{
			char buffer[MAX_PATH] = { 0, };
			SendMessageA(m_hEdit, WM_GETTEXT, MAX_PATH, (LPARAM)buffer);
			JPacket JPacket(PACKET_CHAT_MSG);
			JPacket.m_uPacket.ph.time = timeGetTime();
			JPacket << 999 << "홍길동" << buffer;
			m_Net.SendMsg(m_Net.m_Sock, JPacket.m_uPacket);

			SendMessageA(m_hEdit, WM_SETTEXT, 0, (LPARAM)"");
		}break;
		}
	}break;
	}
	return m_Net.MsgProc(hWnd, msg, wParam, lParam);
}

bool	Sample::Init()
{
	I_Sound.Init();


	m_IntroWorld.Init();
	m_IntroWorld.m_pd3dDevice = m_pd3dDevice.Get();
	m_IntroWorld.m_pContext = m_pImmediateContext.Get();
	m_IntroWorld.Load(L"");
	m_IntroWorld.m_pNextWorld = &m_ZoneWorld;
	//m_ZoneWorld.Init();
	m_ZoneWorld.m_pd3dDevice = m_pd3dDevice.Get();
	m_ZoneWorld.m_pContext = m_pImmediateContext.Get();
	//m_ZoneWorld.Load(L"zone.txt");

	JWorld::m_pWorld = &m_IntroWorld;

	//NetWork
	m_Net.InitNetwork();
	m_Net.Connect(m_hWnd, SOCK_STREAM, 10000, "127.0.0.1");

	return true;
}
bool	Sample::Frame()
{
	JWorld::m_pWorld->Frame();
	

#pragma region

	int iChatCnt = m_Net.m_PlayerUser.m_packetPool.size();
	if (iChatCnt > 0 && m_iChatCnt != iChatCnt)
	{
		m_iChatCnt = iChatCnt;
		SendMessage(m_hListBox, LB_RESETCONTENT, 0, 0);

		std::list<JPacket>::iterator iter;
		if (m_Net.m_PlayerUser.m_packetPool.size() > 20)
		{
			m_Net.m_PlayerUser.m_packetPool.pop_front();
		}
		for (iter = m_Net.m_PlayerUser.m_packetPool.begin();
			iter != m_Net.m_PlayerUser.m_packetPool.end();
			iter++)
		{
			UPACKET& uPacket = (*iter).m_uPacket;
			switch ((*iter).m_uPacket.ph.type)
			{
				case PACKET_LOGIN_ACK:
				{
					DWORD dwCurrent = timeGetTime();
					DWORD dwEnd = 0;
					dwEnd = dwCurrent - uPacket.ph.time;
					JLoginAck ack;
					memcpy(&ack, (*iter).m_uPacket.msg, sizeof(JLoginAck));
					if (ack.iResult == 1)
					{
						int k = 0;
					}
				}break;
				case PACKET_CHAT_MSG:
				{
					DWORD dwCurrent = timeGetTime();
					DWORD dwEnd = 0;
					dwEnd = dwCurrent - uPacket.ph.time;
					if (dwEnd >= 1)
					{
						std::string data = std::to_string(dwEnd);
						data += "\n";
						OutputDebugStringA(data.c_str());
					}
					JChatMsg recvdata;
					ZeroMemory(&recvdata, sizeof(recvdata));
					(*iter) >> recvdata.index >> recvdata.name
						>> recvdata.message;
					SendMessageA(m_hListBox, LB_ADDSTRING, 0,
						(LPARAM)recvdata.message);
				}break;
			}			
			//iter = m_Net.m_PlayerUser.m_packetPool.erase(iter);
			//(*iter).Reset();
		}
		m_Net.m_PlayerUser.m_packetPool.clear();
	}
#pragma endregion  NetProcess
	return true;
}
bool	Sample::Render()
{
	JWorld::m_pWorld->Render();



	std::wstring msg = L"FPS:";
	msg += std::to_wstring(m_GameTimer.m_iFPS);
	msg += L"  GT:";
	msg += std::to_wstring(m_GameTimer.m_fTimer);
	m_dxWrite.Draw(msg, g_rtClient, D2D1::ColorF(0, 0, 1, 1));

	
	return true;
}
bool	Sample::Release()
{	
	I_Sound.Release();
	m_IntroWorld.Release();
	m_ZoneWorld.Release();
	m_Net.CloseNetwork();
	return true;
}
Sample::Sample()
{

}
Sample::~Sample()
{}

RUN()

//#include"JMap.h"
//
//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR    lpCmdLine, int       nCmdShow)
//{
//	JMap a;
//
//
//	a.CreateMap(26, 26, { 0, 0, 780, 780 });
//	std::shared_ptr<JNode> b = a.FIndIndex(750, 750);
//	
//	return 0;
//}
