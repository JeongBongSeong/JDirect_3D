#pragma once
#include "JStd.h"
#include "JBoxObj.h"

class JFrustum : public JBoxObj
{
public:
	T::TPlane m_Plane[6];
	T::TVector3 m_vFrustum[8];
public:
	bool Init();
	void CreateFrustum(T::TMatrix& matView, T::TMatrix& matProj);
public:
	BOOL ClassifyPoint(T::TVector3* v);
	BOOL ClassifySphere(JSphere* v);
	BOOL ClassifyOBB(JBox* v);
public:
	virtual bool SetVertexData();
	virtual bool SetIndexData();
	bool PostRender();

};

