#pragma once
#include"JMatrix.h"
#include"JInput.h"
class JCamera
{
public:
	JVector3 m_vCamera;
	JVector3 m_vTarget;
	JVector3 m_vUp;
public:
	JMatrix m_matWorld;
	JMatrix m_matView;
	JMatrix m_matProj;
public:
	virtual bool Init();
	virtual bool Frame();
	JCamera();
	virtual ~JCamera() {};
};

