#pragma once
#include "JObject2D.h"
class JPlayerObj2D : public JObject2D
{
public:
	virtual void HitOverlap(JBaseObject* pObj, DWORD dwState);
	bool	Frame() override;
public:
	JPlayerObj2D();
	virtual ~JPlayerObj2D();
};
