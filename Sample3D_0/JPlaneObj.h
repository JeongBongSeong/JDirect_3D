#pragma once
#include "JObject3D.h"
class JPlaneObj : public JObject3D
{
public:
	virtual bool SetVertexData() override;
	virtual bool SetIndexData() override;
public:
	JPlaneObj();
	virtual ~JPlaneObj();
};
