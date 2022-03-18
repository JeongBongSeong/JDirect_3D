#pragma once
#include"JWorld.h"
#include "JPlayerObj2D.h"
#include "JObjectNpc2D.h"
#include "JSound.h"
#include "JInput.h"

class JZoneWorld : public JWorld
{
public:
	JInput m_Input;
public:
	JSound* pBackGroundMusic;
public:
	vector<JObjectNpc2D*> m_NpcLlist;
public:
	JPlayerObj2D		m_PlayerObj;
public:
	bool Load(std::wstring file) override;
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();
};

