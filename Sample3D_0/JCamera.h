#pragma once
#include "JStd.h"
class JCamera
{
public:
	JVector3			m_vCamera;
	JVector3			m_vTarget;
	JVector3			m_vUp;

	JMatrix				m_matWorld;
	JMatrix				m_matView;
	JMatrix				m_matProj;
public:
	virtual bool	Init();
	virtual bool	Frame();
	JCamera();
	virtual ~JCamera() {}
};

