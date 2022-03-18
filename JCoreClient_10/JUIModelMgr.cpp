#include "JUIModelMgr.h"
#include "JObjectMgr.h"

bool JUIModelComposed::Frame()
{
	JUIModelComposed* pModel = new JUIModelComposed;
	std::list< JUIModel*>::iterator iter;
	for (iter = m_Components.begin(); iter != m_Components.end();
		iter++)
	{
		(*iter)->Frame();
	}
	return true;
}
bool JUIModelComposed::Render()
{
	JUIModelComposed* pModel = new JUIModelComposed;
	std::list< JUIModel*>::iterator iter;
	for (iter = m_Components.begin(); iter != m_Components.end();
		iter++)
	{
		(*iter)->Render();
	}
	return true;
}
bool	JUIModelComposed::Release()
{
	JUIModelComposed* pModel = new JUIModelComposed;
	std::list< JUIModel*>::iterator iter;
	for (iter = m_Components.begin(); iter != m_Components.end();
		iter++)
	{
		(*iter)->Release();
	}
	return true;
}
void JUIModelComposed::Add(JUIModel* pObj)
{
	m_Components.push_back(pObj);
}
JUIModel* JUIModelComposed::Clone()
{
	JUIModelComposed* pModel = new JUIModelComposed;
	std::list< JUIModel*>::iterator iter;
	for (iter = m_Components.begin(); iter != m_Components.end();
		iter++)
	{
		pModel->Add((*iter)->Clone());

	}
	return pModel;
};

void  JUIModelComposed::UpdateData()
{
	std::list<JUIModel*>::iterator iter;
	for (iter = m_Components.begin(); iter != m_Components.end(); iter++)
	{
		(*iter)->UpdateData();

	}
}