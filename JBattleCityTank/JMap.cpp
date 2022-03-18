#include "JMap.h"

//(x/width) + ((y/height)*y열사이즈) 
//일단 예로 x는 26, y도 26 rt는 30 30 780 780
void JMap::CreateMap(int x, int y, RECT rtClient)
{
	//JVector4 pos = rtClient;
	RECT pos = rtClient;
	LONG startX = pos.left;
	LONG startY = pos.top;
	m_fWidth = rtClient.right / x;		//30
	m_fHeight = rtClient.bottom / y;		//30
	m_iSizeX = x;
	m_iSizeY = y;
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			RECT rtPos = { -1,-1,-1,-1 };
			rtPos.left = pos.left;
			rtPos.top = pos.top;
			rtPos.right = pos.left + m_fWidth;
			rtPos.bottom = pos.top + m_fHeight;
			std::shared_ptr<JNode> newNode(new JNode((i * m_iSizeX) + j, rtPos, m_fWidth, m_fHeight));
			m_vTileList.insert(make_pair((i * m_iSizeX) + j,newNode));
			pos.left = rtPos.right;
		}
		pos.left = startX;
		pos.top = startY+(m_fHeight *(i+1));
	}
	
}


std::shared_ptr<JNode> JMap::FIndIndex(int x, int y)
{
	int iFindIndex = (int)(x / m_fWidth) + ((int)(y / m_fHeight) * m_iSizeY);
	
	std::map<int, std::shared_ptr<JNode>>::iterator iter = m_vTileList.find(iFindIndex);
	
	return iter->second;
}

std::shared_ptr<JNode> JMap::FIndIndex(int iIndex)
{
	
	std::map<int, std::shared_ptr<JNode>>::iterator iter = m_vTileList.find(iIndex);

	return iter->second;
}