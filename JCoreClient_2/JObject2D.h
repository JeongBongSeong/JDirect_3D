#pragma once
#include "JDxObject.h"
class JObject2D : public JDxObject
{
public:
	RECT	m_rtSource;
	RECT	m_rtDraw;
public:
	virtual void SetRectSource(RECT rt);
	virtual void SetRectDraw(RECT rt);
	virtual void AddPosition(JVector2 vPos);
	virtual void SetPosition(JVector2 vPos);
	virtual void UpdateRectDraw(RECT rt);

	// ȭ����ǥ ��ġ�� �������� NDC ��ȯ
	virtual void	Convert(JVector2 center, float fWidth, float fHeight, std::vector<SimpleVertex>& retList);
	// ȭ����ǥ�踦 NDC ��ȯ
	virtual void	Convert(std::vector<SimpleVertex>& list, std::vector<SimpleVertex>& retList);
public:
	virtual bool	SetVertexData() override;

};

