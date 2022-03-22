#include "JCamera.h"

bool JCamera::Init()
{
	m_matView.CreateViewLook(m_vCamera, m_vTarget, m_vDefaultUp);
	// Projection
	m_matProj.PerspectiveFovLH(1.0f, 100.0f, JBASIS_PI * 0.25f, (float)g_rtClient.right / (float)g_rtClient.bottom);
	return true;
}

bool JCamera::Frame()
{
	m_matView.CreateViewLook(m_vCamera, m_vTarget, m_vDefaultUp);
	return true;
}


JCamera::JCamera()
{
	m_vCamera.x = 0.0f;
	m_vCamera.y = 9.0f;
	m_vCamera.z = -15.0f;
	m_vDefaultUp = JVector3(0, 1, 0);
}