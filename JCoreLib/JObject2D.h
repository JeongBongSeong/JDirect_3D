#pragma once
#include "JDxObject.h"
class JObject2D : public JDxObject
{
public:
	std::vector<SimpleVertex> m_VertexList2D;
	RECT	m_rtSource;
	RECT	m_rtDraw;
	T::TVector4			m_vColor;
	T::TVector2	m_vPos;
	T::TVector2	m_vDirection;
public:
	float  m_fAlpha = 0.0f;
	bool   m_bFadeIn = false;
	bool   m_bFadeOut = false;
	virtual void FadeIn();
	virtual void FadeOut();
public:
	virtual void SetRectSource(RECT rt);
	virtual void SetRectDraw(RECT rt);
	virtual void AddPosition(T::TVector2 vPos);
	virtual void SetPosition(T::TVector2 vPos);
	virtual void UpdateRectDraw(RECT rt);
	virtual void UpdateRectSource(RECT rt);

	// ȭ����ǥ ��ġ�� �������� NDC ��ȯ
	virtual void Convert(T::TVector2 center, float fWidth, float fHeight, std::vector<SimpleVertex>& retList);
	// ȭ����ǥ�踦 NDC ��ȯ
	virtual void Convert(std::vector<SimpleVertex>& list, std::vector<SimpleVertex>& retList);
	virtual void ConvertIndex(T::TVector2 center, float fWidth, float fHeight, std::vector<SimpleVertex>& retList);
	// ȭ����ǥ�踦 NDC ��ȯ
	virtual void ConvertIndex(std::vector<SimpleVertex>& list, std::vector<SimpleVertex>& retList);
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
	JObject2D();
	virtual ~JObject2D();
};

