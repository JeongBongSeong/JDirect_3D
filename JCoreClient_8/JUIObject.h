#pragma once
#include"JObject2D.h"
#include "JWorld.h"
class JUIObject : public JObject2D
{
public:
	bool Frame() override;
	bool Render() override;
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

