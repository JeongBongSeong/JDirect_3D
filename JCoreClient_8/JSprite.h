#pragma once

#include<JObject2D.h>

class JSprite : public JObject2D
{
public:
	float m_fAnimTime;
	std::vector<RECT> m_rtArray;
public:
	void			SetRectSourceArray(RECT rt);
	virtual bool	Init() override;
	virtual bool	Frame()override;
	virtual bool	Render()override;
	virtual bool	Release()override;
public:
	bool Load(ID3D11Device* pd3dDevice, std::wstring filename);
};

class JSpriteMgr : public JBaseMgr<JSprite, JSpriteMgr>
{
	friend JSingleton< JSpriteMgr>;
public:
	JSprite* Load(std::wstring filename) override;
private:
	JSpriteMgr();
public:
	virtual ~JSpriteMgr();
};

#define I_Sprite JSpriteMgr::Get()