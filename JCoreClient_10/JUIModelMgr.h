#pragma once
#include"JBaseMgr.h"
#include"JObject2D.h"

class JUIModel : public JObject2D
{
public:
	JUIModel* m_pParent = nullptr;
public:
	virtual JUIModel* Clone() { return nullptr; };
	bool Load(ID3D11Device* pd3dDevice, std::wstring filename) { return true; };
	virtual void UpdateData() {}

};
class JUIModelComposed : public JUIModel
{
public:
	std::list<JUIModel*> m_Components;
public:
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
	virtual void Add(JUIModel* pObj);
	virtual JUIModel* Clone();
	virtual bool Load(ID3D11Device* pd3dDevice, std::wstring filename) 
	{
		return true;
	};
	virtual void  UpdateData();
};

class JUIModelMgr : public JBaseMgr<JUIModel , JUIModelMgr>
{
	friend class JSingleton<JUIModelMgr>;
private:
	JUIModelMgr() {};
public:
	~JUIModelMgr() {};

};

#define I_UI JUIModelMgr::Get()