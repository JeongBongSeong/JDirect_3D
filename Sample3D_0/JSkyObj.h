#pragma once
#include "JObject3D.h"
class JSkyObj : public JObject3D
{
public:
	JMatrix m_matViewSky;
	JTexture* m_pTexArray[6];
public:
	virtual bool		LoadTexture(const TCHAR* szColorFileName, const TCHAR* szMaskFileName);
	virtual bool		SetVertexData();
	virtual bool		SetIndexData();
	bool	PostRender();
public:
	JSkyObj();
	virtual ~JSkyObj();
};