#include "JCamera.h"
#include "JInput.h"
bool JCamera::Init()
{
	m_matView.CreateViewLook(m_vCamera, m_vTarget, m_vDefaultUp);
	// Projection
	m_matProj.PerspectiveFovLH(0.1f, 10000.0f,
		JBASIS_PI * 0.25f,
		(float)g_rtClient.right / (float)g_rtClient.bottom);
	return true;
}
bool JCamera::Frame()
{
	/*if (TInput::Get().GetKey(VK_LEFT))
	{
		m_vCamera.z -= g_fSecPerFrame * 1.0f;
	}
	if (TInput::Get().GetKey(VK_RIGHT))
	{
		m_vCamera.z += g_fSecPerFrame * 1.0f;
	}
	if (TInput::Get().GetKey(VK_UP))
	{
		m_vCamera.y += g_fSecPerFrame * 1.0f;
	}
	if (TInput::Get().GetKey(VK_DOWN))
	{
		m_vCamera.y -= g_fSecPerFrame * 1.0f;
	}*/
	m_matView.CreateViewLook(m_vCamera, m_vTarget, m_vDefaultUp);
	
	m_vRight.x = m_matWorld._11;
	m_vRight.y = m_matWorld._21;
	m_vRight.z = m_matWorld._31;
	m_vUp.x = m_matWorld._12;
	m_vUp.y = m_matWorld._22;
	m_vUp.z = m_matWorld._32;
	m_vLook.x = m_matWorld._13;
	m_vLook.y = m_matWorld._23;
	m_vLook.z = m_matWorld._33;
	

	return true;
}
JCamera::JCamera()
{
	m_vCamera.x = 0.0f;
	m_vCamera.y = 200.0f;
	m_vCamera.z = -15.0f;
	m_vDefaultUp = JVector3(0, 1, 0);
}