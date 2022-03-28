#pragma once
#include "JObject3D.h"
class JBoxObj : public JObject3D
{
public:
	JTexture* m_pTexCube;
public:
	virtual bool SetVertexData() override;
	virtual bool SetIndexData() override;
public:
	bool	PostRender();
public:
	JBoxObj();
	virtual ~JBoxObj();
};


