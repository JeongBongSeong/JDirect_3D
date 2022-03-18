#pragma once
#include "JDxObject.h"
class JObject2D : public JDxObject
{
public:
	RECT	m_rtSource;
	RECT	m_rtDraw;
	JVector4			m_vColor;
public:
	float  m_fAlpha = 0.0f;
	bool   m_bFadeIn = false;
	bool   m_bFadeOut = false;
	virtual void FadeIn();
	virtual void FadeOut();
public:
	virtual void SetRectSource(RECT rt);
	virtual void SetRectDraw(RECT rt);
	virtual void AddPosition(JVector2 vPos);
	virtual void SetPosition(JVector2 vPos);
	virtual void UpdateRectDraw(RECT rt);
	virtual void UpdateRectSource(RECT rt);

	// 화면좌표 위치를 중점으로 NDC 변환
	virtual void Convert(JVector2 center, float fWidth, float fHeight, std::vector<SimpleVertex>& retList);
	// 화면좌표계를 NDC 변환
	virtual void Convert(std::vector<SimpleVertex>& list, std::vector<SimpleVertex>& retList);
	virtual void ConvertIndex(JVector2 center, float fWidth, float fHeight, std::vector<SimpleVertex>& retList);
	// 화면좌표계를 NDC 변환
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

