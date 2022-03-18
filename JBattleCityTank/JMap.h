#pragma once
#include"JStd.h"

struct JNode
{
public:
	int m_iTileID;
	RECT m_rtPos;
	float m_fWidth;
	float m_fHeight;

	JNode()
	{
		m_iTileID = -1;
		m_rtPos = { 0,0,0,0 };
		m_fWidth = 0.0f;
		m_fHeight = 0.0f;
	};
	JNode(int iId,RECT rtPos, float width, float height)
	{
		m_iTileID = iId;
		m_rtPos = rtPos;
		m_fWidth = width;
		m_fHeight = height;
	};
};

class JMap
{
public:
	std::map<int,std::shared_ptr<JNode>> m_vTileList;
	int m_iSizeX;
	int m_iSizeY;
	float m_fWidth;
	float m_fHeight;
public:
	void CreateMap(int x, int y, RECT rtClient);	// x는 가로노드의 개수 y는 세로 노드의 개수  rtClient는 시작위치와 가로 세로 길이
	std::shared_ptr<JNode> FIndIndex(int x, int y);
	std::shared_ptr<JNode> FIndIndex(int iIndex);
};
