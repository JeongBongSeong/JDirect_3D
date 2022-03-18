#pragma once
#include"JUIModelMgr.h"
#include "JWorld.h"
#include "JSoundMgr.h"
#include "JUIObject.h"
#include "JObjectMgr.h"
struct JStatePlayData
{
	JTexture* pTex;
	JSound* pSound;
	JStatePlayData(const JStatePlayData& data)
	{
		pTex = data.pTex;
		pSound = data.pSound;
		DisplayText("JStatePlayDataCopy\n");
	}
	JStatePlayData()
	{
		DisplayText("JStatePlayData\n");
	}
	JStatePlayData(JTexture* a, JSound* b)
	{
		pTex = a;
		pSound = b;
		DisplayText("JStatePlayData\n");
	}
};

class JUIObject : public JUIModel
{
	JUIModel* Clone()
	{
		JUIModel* pCopy = new JUIObject(*this);
		pCopy->CreateVertexBuffer();
		pCopy->CreateIndexBuffer();
		pCopy->CreateConstantBuffer();
		pCopy->CreateInputLayout();
		D3D11_BLEND_DESC  blenddesc;
		ZeroMemory(&blenddesc, sizeof(D3D11_BLEND_DESC));
		/*bd.AlphaToCoverageEnable;
		bd.IndependentBlendEnable;*/
		blenddesc.RenderTarget[0].BlendEnable = TRUE;
		blenddesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blenddesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blenddesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		//// A 연산 저장
		blenddesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blenddesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blenddesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blenddesc.RenderTarget[0].RenderTargetWriteMask =
			D3D11_COLOR_WRITE_ENABLE_ALL;
		HRESULT hr = m_pd3dDevice->CreateBlendState(&blenddesc, &m_pAlphaBlend);

		blenddesc.RenderTarget[0].BlendEnable = FALSE;
		hr = m_pd3dDevice->CreateBlendState(&blenddesc, &m_pAlphaBlendDisable);
		return pCopy;
	};
	void  UpdateData()
	{
		m_rtCollision = JRect(m_vPos, m_fWidth, m_fHeight);
		I_ObjectMgr.AddCollisionExecute(this,
			std::bind(&JBaseObject::HitOverlap, this,
				std::placeholders::_1,
				std::placeholders::_2));
		I_ObjectMgr.AddSelectExecute(this,
			std::bind(&JBaseObject::HitSelect, this,
				std::placeholders::_1,
				std::placeholders::_2));
	}
public:
	std::vector<JStatePlayData> m_pStatePlayList;
	RECT m_rtOffset;
	RECT m_rtOffsetTex;
public:
	bool Frame() override;
	bool Render() override;
public:
	bool SetVertexData()override;
	bool SetIndexData()override;
public:
	JUIObject()
	{
		m_rtOffsetTex.left = 0;
		m_rtOffsetTex.top = 0;
		m_rtOffsetTex.right = 1;
		m_rtOffsetTex.bottom = 1;
	}
};


class JImageObject : public JUIObject
{
	JUIModel* Clone()
	{
		JUIModel* pCopy = new JImageObject(*this);
		pCopy->CreateVertexBuffer();
		pCopy->CreateIndexBuffer();
		pCopy->CreateConstantBuffer();
		pCopy->CreateInputLayout();
		D3D11_BLEND_DESC  blenddesc;
		ZeroMemory(&blenddesc, sizeof(D3D11_BLEND_DESC));
		/*bd.AlphaToCoverageEnable;
		bd.IndependentBlendEnable;*/
		blenddesc.RenderTarget[0].BlendEnable = TRUE;
		blenddesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blenddesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blenddesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		//// A 연산 저장
		blenddesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blenddesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blenddesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blenddesc.RenderTarget[0].RenderTargetWriteMask =
			D3D11_COLOR_WRITE_ENABLE_ALL;
		HRESULT hr = m_pd3dDevice->CreateBlendState(&blenddesc, &m_pAlphaBlend);

		blenddesc.RenderTarget[0].BlendEnable = FALSE;
		hr = m_pd3dDevice->CreateBlendState(&blenddesc, &m_pAlphaBlendDisable);
		return pCopy;
	};
	void  UpdateData()
	{
		m_rtCollision = JRect(m_vPos, m_fWidth, m_fHeight);
		I_ObjectMgr.AddCollisionExecute(this,
			std::bind(&JBaseObject::HitOverlap, this,
				std::placeholders::_1,
				std::placeholders::_2));
		I_ObjectMgr.AddSelectExecute(this,
			std::bind(&JBaseObject::HitSelect, this,
				std::placeholders::_1,
				std::placeholders::_2));
	}
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
};

class JButtonObject : public JUIObject
{
public:
	JUIModel* Clone()
	{
		JUIModel* pCopy = new JButtonObject(*this);
		pCopy->CreateVertexBuffer();
		pCopy->CreateIndexBuffer();
		pCopy->CreateConstantBuffer();
		pCopy->CreateInputLayout();
		D3D11_BLEND_DESC  blenddesc;
		ZeroMemory(&blenddesc, sizeof(D3D11_BLEND_DESC));
		/*bd.AlphaToCoverageEnable;
		bd.IndependentBlendEnable;*/
		blenddesc.RenderTarget[0].BlendEnable = TRUE;
		blenddesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blenddesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blenddesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		//// A 연산 저장
		blenddesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blenddesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blenddesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blenddesc.RenderTarget[0].RenderTargetWriteMask =
			D3D11_COLOR_WRITE_ENABLE_ALL;
		HRESULT hr = m_pd3dDevice->CreateBlendState(&blenddesc, &m_pAlphaBlend);

		blenddesc.RenderTarget[0].BlendEnable = FALSE;
		hr = m_pd3dDevice->CreateBlendState(&blenddesc, &m_pAlphaBlendDisable);
		return pCopy;
	};
	void  UpdateData()
	{
		m_rtCollision = JRect(m_vPos, m_fWidth, m_fHeight);
		I_ObjectMgr.AddCollisionExecute(this,
			std::bind(&JBaseObject::HitOverlap, this,
				std::placeholders::_1,
				std::placeholders::_2));
		I_ObjectMgr.AddSelectExecute(this,
			std::bind(&JBaseObject::HitSelect, this,
				std::placeholders::_1,
				std::placeholders::_2));
	};
public:
	virtual void	HitSelect(JBaseObject* pObj, DWORD dwState) override;
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
public:
	JButtonObject() {}
	virtual ~JButtonObject() {}
};

