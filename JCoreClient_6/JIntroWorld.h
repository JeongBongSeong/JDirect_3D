#pragma once
#include"JWorld.h"
#include "JPlayerObj2D.h"
#include "JObjectNpc2D.h"
#include "JSound.h"
#include "JInput.h"

class JIntroWorld : public JWorld
{
public:
	JInput m_Input;
public:
	JSound* m_pBackGroundMusic;

public:
	JObject2D		m_PlayerObj;
public:
	bool Load(std::wstring file) override;
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();
};

