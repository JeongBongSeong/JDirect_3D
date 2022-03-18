#pragma once
#include"JUIModelMgr.h"
#include "JWorld.h"
#include "JUIObject.h"
#include "JObjectMgr.h"

class JUIObject : public JUIModel
{
	JUIModel* Clone()
	{
		JUIModel* pCopy = new JUIObject(*this);
		pCopy->CreateVertexBuffer();
		pCopy->CreateIndexBuffer();
		pCopy->CreateConstantBuffer();
		pCopy->CreateInputLayout();

		return pCopy;
	};
	void  UpdateData() override
	{
		m_rtCollision = JRect(m_vPos, m_fWidth, m_fHeight);
		SetCollisionType(JCollisionType::Ignore, JSelectType::Select_Overlap);
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
	bool Frame() override;
	bool Render() override;
public:
	bool SetVertexData()override;
	bool SetIndexData()override;
	void HitSelect(JBaseObject* pObj, DWORD dwState) override
	{
		int k = 0;
	}
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
public:
	void    HitSelect(JBaseObject* pObj, DWORD dwState) override
	{
		int k = 0;
	}
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

		return pCopy;
	};
	void  UpdateData() override
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

class JListCtrlObject : public JUIModelComposed
{
public:
	JUIModel* Clone()
	{
		JUIModelComposed* pModel = new JListCtrlObject;
		std::list< JUIModel*>::iterator iter;
		for (iter = m_Components.begin(); iter != m_Components.end();
			iter++)
		{
			pModel->Add((*iter)->Clone());
		}
		return pModel;
	};
	bool   Create(int xCount, int yCount);
	void  UpdateData()
	{
		m_rtCollision = JRect(m_vPos, m_fWidth, m_fHeight);
		SetCollisionType(JCollisionType::Ignore,
			JSelectType::Select_Overlap);

		I_ObjectMgr.AddCollisionExecute(this,
			std::bind(&JBaseObject::HitOverlap, this,
				std::placeholders::_1,
				std::placeholders::_2));
		I_ObjectMgr.AddSelectExecute(this,
			std::bind(&JBaseObject::HitSelect, this,
				std::placeholders::_1,
				std::placeholders::_2));
	}
	virtual void	HitSelect(JBaseObject* pObj, DWORD dwState) override;
public:
	JListCtrlObject() {}
	virtual ~JListCtrlObject() {}
};