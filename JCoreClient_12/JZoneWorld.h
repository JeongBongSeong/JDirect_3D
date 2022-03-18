#pragma once
#include"JWorld.h"
#include "JPlayerObj2D.h"
#include "JObjectNpc2D.h"
#include "JSoundMgr.h"
#include "JInput.h"

class JZoneWorld : public JWorld
{
public:
	JSound* m_pBackGroundMusic;
public:
	JPlayerObj2D		m_PlayerObj;
public:
	bool Load(std::wstring file) override;
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();
};

