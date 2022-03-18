#pragma once
#include"JWorld.h"
#include "JPlayerObj2D.h"
#include "JObjectNpc2D.h"
#include "JUIObject.h"
#include "JSoundMgr.h"
#include "JShaderMgr.h"
#include "JTextureMgr.h"
#include "JInput.h"

class JIntroWorld : public JWorld
{
public:
	JSound* m_pBackGroundMusic;
	JTexture* m_pChangeColorTex[10];
	JTexture* m_pColorTex;
public:
	JObject2D		m_PlayerObj;
public:
	bool Load(std::wstring file) override;
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();
};

