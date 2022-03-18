#pragma once
#include"JBaseMgr.h"
#include"JObject2D.h"
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

class JUIModel : public JObject2D
{
public:
	std::vector<JStatePlayData> m_pStatePlayList;
	RECT	m_rtOffset;
	RECT	m_rtOffsetTex;
public:
	virtual JUIModel* Clone() { return nullptr; };
	virtual void UpdateData() {}

};
class JUIModelComposed : public JUIModel
{
public:
	std::list<JUIModel*> m_Components;
public:
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
	virtual void Add(JUIModel* pObj);
	virtual JUIModel* Clone();
	virtual void  UpdateData();
};

class JUIModelMgr : public JBaseMgr<JUIModel , JUIModelMgr>
{
	friend class JSingleton<JUIModelMgr>;
private:
	JUIModelMgr() {};
public:
	~JUIModelMgr() {};

};

#define I_UI JUIModelMgr::Get()