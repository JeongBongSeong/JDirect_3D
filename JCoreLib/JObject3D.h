#pragma once
#include "JDxObject.h"
class JObject3D : public JDxObject
{
public:
	T::TVector3 m_vPos;
	T::TVector3 m_vDirection;
	T::TVector4 m_vColor;
	T::TMatrix m_matWorld;
	T::TMatrix m_matView;
	T::TMatrix m_matProj;
	T::TVector3 m_vRight;
	T::TVector3 m_vLook;
	T::TVector3 m_vUp;
public:
	float  m_fAlpha = 0.0f;
	bool   m_bFadeIn = false;
	bool   m_bFadeOut = false;
public:
	virtual void FadeIn();
	virtual void FadeOut();
public:
	virtual void AddPosition(T::TVector3 vPos);
	virtual void SetPosition(T::TVector3 vPos);
public:
	virtual bool SetVertexData() override;
	virtual bool SetIndexData() override;
public:
	virtual bool Frame() override;
public:
	virtual void GenAABB();
public:
	bool Load(ID3D11Device* pd3dDevice, std::wstring filename) {
		return true;
	};
public:
	virtual void UpdateData();
	virtual void UpdateCollision();
	virtual void SetMatrix(T::TMatrix* matWorld, T::TMatrix* matView, T::TMatrix* matProj);
public:
	JObject3D();
	virtual ~JObject3D();
};
