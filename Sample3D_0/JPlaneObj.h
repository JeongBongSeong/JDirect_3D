#pragma once
#include "JObject3D.h"
class JPlaneObj : public JObject3D
{
	JVector3			m_vCamera;
	JMatrix				m_matWorld;
	JMatrix				m_matView;
	JMatrix				m_matProj;
public:
	virtual bool SetVertexData() override;
public:
	virtual bool SetIndexData() override;
public:
	virtual bool Frame();
public:
	JPlaneObj()
	{
		m_vCamera.x = 0.0f;
		m_vCamera.y = 0.0f;
		m_vCamera.z = -5.0f;
	}
};
