//��ġ46 62  ũ��67 78
#include "Sample.h"
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
			JPacket << 999 << "ȫ�浿" << buffer;
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
	/*DWORD style = WS_CHILD | WS_VISIBLE | ES_MULTILINE ;
	m_hEdit = CreateWindow(L"edit", NULL, style,
		0, g_rtClient.bottom-50, 300, 50,
		m_hWnd, (HMENU)100, m_hInstance, NULL);
	style = WS_CHILD | WS_VISIBLE;
	m_hButton = CreateWindow(L"button", L"����", style,
		310, g_rtClient.bottom - 50, 50, 50,
		m_hWnd, (HMENU)200, m_hInstance, NULL);
	m_hListBox = CreateWindow(L"listbox", NULL, style,
		0, 0, 300, g_rtClient.bottom - 70,
		m_hWnd, (HMENU)300, m_hInstance, NULL);
	SendMessageA(m_hListBox, LB_ADDSTRING, 0, (LPARAM)"ä�ý���!");*/

	/*for (int iObj = 0; iObj < 12; iObj++)
	{
		TDxObject obj;
		obj.Init();
		///0 ~ g_rtClient
		if (obj.Create(m_pd3dDevice, m_pImmediateContext,
			TVector2(-100 * iObj, iObj * 50), 400, 30))
		{
			m_ObjectList.push_back(obj);
		}
	}*/
	JShader* pVShader = I_Shader.CreateVertexShader(m_pd3dDevice.Get(), L"VertexShader.txt", "VS");
	JShader* pPShader = I_Shader.CreatePixelShader(m_pd3dDevice.Get(), L"PixelShader.txt", "PS");

	m_PlayerObj.Init();
	m_PlayerObj.SetRectSource({ 91,1,42,56 });
	//m_PlayerObj.SetRectSouce({ 46,63,69,79 });
	m_PlayerObj.SetRectDraw({ 0,0, 42,56 });
	m_PlayerObj.SetPosition(JVector2(400, 300));
	m_PlayerObj.m_pVShader = pVShader;
	m_PlayerObj.m_pPShader = pPShader;
	if (!m_PlayerObj.Create(m_pd3dDevice.Get(), m_pImmediateContext.Get(),
		nullptr,
		L"../../data/BattleCity/ObjectList.png"
	//	L"../../data/BattleCity/ObjectList_White.png"
	))
	{
		return false;
	}

	for (int iNpc = 0; iNpc < 5; iNpc++)
	{
		JObjectNpc2D* npc = new JObjectNpc2D();
		npc->Init();
		if (iNpc % 2 == 0)
		{
			npc->SetRectSource({ 46,63,69,79 });
			npc->SetRectDraw({ 0,0, 69,79 });
		}
		else
		{
			npc->SetRectSource({ 1,63,42,76 });
			npc->SetRectDraw({ 0,0, 42,76 });
		}

		npc->SetPosition(JVector2(50 + iNpc * 150, 50));

		npc->m_pVShader = pVShader;
		npc->m_pPShader = pPShader;

		if (!npc->Create(m_pd3dDevice.Get(), m_pImmediateContext.Get(),
			nullptr,
			L"../../data/bitmap1.bmp",
			L"../../data/bitmap2.bmp"))
		{
			return false;
		}
		m_NpcLlist.push_back(npc);
	}
	



	m_Net.InitNetwork();
	m_Net.Connect(m_hWnd, SOCK_STREAM, 10000, "127.0.0.1");

	return true;
}
bool	Sample::Frame()
{
	m_PlayerObj.Frame();

	for (int iObj = 0; iObj < m_NpcLlist.size(); iObj++)
	{
		RECT rt = m_NpcLlist[iObj]->m_rtDraw;
		rt.right = rt.right + (cos(g_fGameTimer) * 0.5f + 0.5f) * 50.0f;
		rt.bottom = rt.bottom + (cos(g_fGameTimer) * 0.5f + 0.5f) * 50.0f;
		m_NpcLlist[iObj]->UpdateRectDraw(rt);
		m_NpcLlist[iObj]->Frame();
	}

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

	return true;
}
bool	Sample::Render()
{
	
	for (int iObj = 0; iObj < m_NpcLlist.size(); iObj++)
	{
		m_NpcLlist[iObj]->Render();
	}
	m_PlayerObj.Render();
	return true;
}
bool	Sample::Release()
{	
	
	for (int iObj = 0; iObj < m_NpcLlist.size(); iObj++)
	{
		m_NpcLlist[iObj]->Release();
	}
	m_PlayerObj.Release();

	m_Net.CloseNetwork();
	return true;
}
Sample::Sample()
{

}
Sample::~Sample()
{}

RUN()