#include "JCamera.h"
#include "JInput.h"

void JCamera::CreateViewMatrix(T::TVector3 p, T::TVector3 t, T::TVector3 u)
{
	m_vCamera = p;
	m_vTarget = t;
	m_vDefaultUp = u;
	T::D3DXMatrixLookAtLH(&m_matView, &m_vCamera, &m_vTarget, &m_vDefaultUp);
	UpdateVector();
}

void JCamera::CreateProjMatrix(float fovy,float aspect,float zn, float zf)
{
	T::D3DXMatrixPerspectiveFovLH(&m_matProj, fovy, aspect, zn, zf);
}
bool JCamera::Init()
{
	//Lookat
	CreateViewMatrix(m_vCamera, m_vTarget, m_vDefaultUp);

	// Projection
	CreateProjMatrix(0.1f, 10000.0f, JBASIS_PI * 0.25f,	
		(float)g_rtClient.right / (float)g_rtClient.bottom);
	UpdateVector();

	return true;
}
bool JCamera::Update(T::TVector4 vDirValue)
{
	T::TMatrix matRotation;
	T::D3DXQuaternionRotationYawPitchRoll(&m_qRotation,
		vDirValue.y,
		vDirValue.x,
		vDirValue.z);

	m_vCamera += m_vLook * vDirValue.w;
	m_fRadius += vDirValue.w;

	T::D3DXMatrixAffineTransformation(&matRotation, 1.0f, NULL,
		&m_qRotation, &m_vCamera);
	T::D3DXMatrixInverse(&m_matView, NULL, &matRotation);

	return UpdateVector();
}
bool JCamera::UpdateVector()
{
	m_vRight.x = m_matView._11;
	m_vRight.y = m_matView._21;
	m_vRight.z = m_matView._31;
	m_vUp.x = m_matView._12;
	m_vUp.y = m_matView._22;
	m_vUp.z = m_matView._32;
	m_vLook.x = m_matView._13;
	m_vLook.y = m_matView._23;
	m_vLook.z = m_matView._33;
	CreateFrustum(m_matView, m_matProj);
	return true;
}
void JCamera::MoveLook(float fValue)
{
	m_vCamera += m_vLook * fValue;
}
void JCamera::MoveSide(float fValue)
{
	m_vCamera += m_vRight * fValue;
}
void JCamera::MoveUp(float fValue)
{
	m_vCamera += m_vUp * fValue;
}
bool JCamera::Frame()
{
	// 마우스 회전
	T::TVector2 dir = JInput::Get().GetDelta();
	if (JInput::Get().GetKey(VK_SPACE) == KEY_HOLD)
		m_bSpaceRun = true;
	else
		m_bSpaceRun = false;

	if (!m_bSpaceRun)
		m_fSpeed = 100.0f;
	else
		m_fSpeed = 300.0f;

	if (JInput::Get().GetKey('A') || JInput::Get().GetKey(VK_LEFT))
	{
		MoveSide(-g_fSecPerFrame * m_fSpeed);
	}
	if (JInput::Get().GetKey('D') || JInput::Get().GetKey(VK_RIGHT))
	{
		MoveSide(g_fSecPerFrame * m_fSpeed);
	}
	if (JInput::Get().GetKey('W') || JInput::Get().GetKey(VK_UP))
	{
		MoveLook(g_fSecPerFrame * m_fSpeed);
	}
	if (JInput::Get().GetKey('S') || JInput::Get().GetKey(VK_DOWN))
	{
		MoveLook(-g_fSecPerFrame * m_fSpeed);
	}
	Update(T::TVector4(-dir.x, -dir.y, 0, 0));
	//T::D3DXMatrixLookAtLH(&m_matView,&m_vCamera, &m_vTarget, &m_vDefaultUp);
	return UpdateVector();
}
JCamera::JCamera()
{
	m_vCamera.x = 0.0f;
	m_vCamera.y = 0.0f;
	m_vCamera.z = 0.0f;
	m_vTarget.x = 0;
	m_vTarget.y = 0;
	m_vTarget.z = 100;
	m_vUp = m_vDefaultUp = T::TVector3(0, 1, 0);
}