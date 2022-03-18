#pragma once
#include "JObject2D.h"
class JObjectNpc2D : public JObject2D
{
public:
	bool Frame() override;
public:
	void HitOverlap(JBaseObject* pObj, DWORD dwState);
public:
	JObjectNpc2D();
	virtual ~JObjectNpc2D();
};