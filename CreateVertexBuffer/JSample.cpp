#include "JSample.h"

JSample::JSample()
{
}
JSample::~JSample()
{
}
bool JSample::Init()
{
	for (int iObj = 0; iObj < 12; iObj++)
	{
		JDxObject obj;
		obj.Init();

		//0 ~ g_rtClient
		if (obj.Create(m_pd3dDevice, m_pImmediateContext,
			JVector2(-100 * iObj, iObj * 50), 400, 30))
		{
			m_ObjectList.push_back(obj);
		}
	}
	return true;
}

bool JSample::Frame()
{
	for (int iObj = 0; iObj < m_ObjectList.size(); iObj++)
	{
		m_ObjectList[iObj].Frame();
	}
	return true;
}

bool JSample::Render()
{
	for (int iObj = 0; iObj < m_ObjectList.size(); iObj++)
	{
		m_ObjectList[iObj].Render();
	}
	return true;
}

bool JSample::Release()
{
	for (int iObj = 0; iObj < m_ObjectList.size(); iObj++)
	{
		m_ObjectList[iObj].Release();
	}
	return true;
}

GAME_RUN(JBS Title, 1024, 768)