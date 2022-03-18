#pragma once
#include"JObject2D.h"
#include "JWorld.h"
#include "JSoundMgr.h"

struct JStatePlayData
{
	JTexture* pTex;
	JSound* pSound;
	JStatePlayData(const JStatePlayData& data)
	{
		pTex = data.pTex;
		pSound = data.pSound;
		DisplayText("JStatePlayDataCopy\n");
	}
	JStatePlayData()
	{
		DisplayText("JStatePlayData\n");
	}
	JStatePlayData(JTexture* a, JSound* b)
	{
		pTex = a;
		pSound = b;
		DisplayText("JStatePlayData\n");
	}
};

class JUIObject : public JObject2D
{
public:
	std::vector<JStatePlayData> m_pStatePlayList;
	RECT m_rtOffset;
	RECT m_rtOffsetTex;
public:
	bool Frame() override;
	bool Render() override;
public:
	bool SetVertexData()override;
	bool SetIndexData()override;
public:
	JUIObject()
	{
		m_rtOffsetTex.left = 0;
		m_rtOffsetTex.top = 0;
		m_rtOffsetTex.right = 1;
		m_rtOffsetTex.bottom = 1;
	}
};


class JImageObject : public JUIObject
{
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
};

class JButtonObject : public JUIObject
{
public:
	virtual void	HitSelect(JBaseObject* pObj, DWORD dwState) override;
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
};

