#pragma once
#include "JObject3D.h"
class JBoxObj : public JObject3D
{
public:
	virtual bool SetVertexData() override;
public:
	virtual bool SetIndexData() override;
};


