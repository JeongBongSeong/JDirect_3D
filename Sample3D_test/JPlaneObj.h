#pragma once
#include "JObject3D.h"
class JPlaneObj : public JObject3D
{
public:
	virtual bool		SetVertexData();
	virtual bool		SetIndexData();
public:
	JPlaneObj();
	virtual ~JPlaneObj() {};
};
