#pragma once
#include "JDxObject.h"
class JObject3D : public JDxObject
{
public:
	JVector3 m_vPos;
	JVector3 m_vDirection;
	JVector4 m_vColor;
public:
	float  m_fAlpha = 0.0f;
	bool   m_bFadeIn = false;
	bool   m_bFadeOut = false;
public:
	virtual void FadeIn();
	virtual void FadeOut();
public:
	virtual void AddPosition(JVector3 vPos);
	virtual void SetPosition(JVector3 vPos);
public:
	virtual bool SetVertexData() override;
	virtual bool SetIndexData() override;
public:
	virtual bool Frame() override;
public:
	bool Load(ID3D11Device* pd3dDevice, std::wstring filename) {
		return true;
	};
public:
	virtual void UpdateData() {};
public:
	JObject3D();
	virtual ~JObject3D();
};
