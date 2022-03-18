#pragma once
#include"JWorld.h"
#include "JPlayerObj2D.h"
#include "JObjectNpc2D.h"
#include "JUIObject.h"
#include "JSoundMgr.h"
#include "JShaderMgr.h"
#include "JTextureMgr.h"
#include "JInput.h"
#include "JEffectObj.h"
#include "JObjectMgr.h"

class JIntroWorld : public JWorld
{
public:
	//JSprite m_SpriteObj;
	JButtonObject* m_btnObj;
	JEffectObj m_ExplosionObj;
	JSound* m_pBackGroundMusic;
	JTexture* m_pChangeColorTex[10];
	JTexture* m_pColorTex;
public:
	JWorld* m_pNextWorld;		// 다음 월드 이동
public:
	bool CreateModelType();
	bool Load(std::wstring file) override;
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();
};

