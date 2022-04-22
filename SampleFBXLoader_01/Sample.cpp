#include "Sample.h"
#include "JObjectMgr.h"
//Remote: error: File lib / libfbxsdk - md.lib is 257.27 MB; this exceeds GitHub's file size limit of 100.00 MB        
//Remote: error: File lib / libfbxsdk - mt.lib is 282.44 MB; this exceeds GitHub's file size limit of 100.00 MB  


void	Sample::CreateResizeDevice(UINT iWidth, UINT iHeight)
{
	int k = 0;
}
void	Sample::DeleteResizeDevice(UINT iWidth, UINT iHeight)
{
	int k = 0;
}
bool	Sample::Init()
{
	std::vector<std::wstring> listname;
	//listname.push_back(L"../../data/fbx/Man.fbx");
	//listname.push_back(L"../../data/fbx/MultiCameras.fbx");
	/*listname.push_back(L"../../data/fbx/SM_Barrel.fbx");
	listname.push_back(L"../../data/fbx/SM_Rock.fbx");
	listname.push_back(L"../../data/fbx/MultiCameras.fbx");
	listname.push_back(L"../../data/fbx/st00sc00.fbx");
	listname.push_back(L"../../data/fbx/SM_Tree_Var01.fbx");*/
	listname.push_back(L"../../data/fbx/Greystone.fbx");
	listname.push_back(L"../../data/fbx/idle.fbx");
	listname.push_back(L"../../data/fbx/Turret_Deploy1/Turret_Deploy1.fbx");

	I_ObjectMgr.Set(m_pd3dDevice.Get(), m_pImmediateContext.Get());
	m_FbxObj.resize(listname.size());

	for(int iObj=0; iObj < listname.size(); iObj++)
	{
		JFbx* fbx = &m_FbxObj[iObj];
		fbx->Init();
		fbx->m_pd3dDevice = m_pd3dDevice.Get();
		fbx->m_pContext = m_pImmediateContext.Get();
		fbx->m_pMeshImp = I_ObjectMgr.Load(listname[iObj]);
		fbx->m_DrawList.resize(fbx->m_pMeshImp->m_DrawList.size());
		fbx->SetPosition(T::TVector3(iObj * 100.0f, 0, 0));
		for (int iDraw = 0; iDraw < fbx->m_pMeshImp->m_DrawList.size(); iDraw++)
		{
			fbx->m_pMeshImp->m_DrawList[iDraw]->m_pContext = m_pImmediateContext.Get();
		}
	}

	m_FbxObj[0].m_pAnimImporter = m_FbxObj[1].m_pMeshImp;
	m_pMainCamera->CreateViewMatrix(T::TVector3(0, 25.0f, -50.0f),
		T::TVector3(0, 0.0f, 0));

	return true;
}
bool	Sample::Frame()
{
	
	for (int iObj = 0; iObj <m_FbxObj.size(); iObj++)
	{
		m_FbxObj[iObj].Frame();
	}
	return true;
}
bool	Sample::Render()
{
	for (int iObj = 0; iObj < m_FbxObj.size(); iObj++)
	{
		m_FbxObj[iObj].SetMatrix(&m_FbxObj[iObj].m_matWorld, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
		m_FbxObj[iObj].Render();
	}
	std::wstring msg = L"FPS:";
	msg += std::to_wstring(m_GameTimer.m_iFPS);
	msg += L"  GT:";
	msg += std::to_wstring(m_GameTimer.m_fTimer);
	m_dxWrite.Draw(msg, g_rtClient, D2D1::ColorF(0, 0, 1, 1));
	return true;
}
bool	Sample::Release()
{
	for (int iObj = 0; iObj < m_FbxObj.size(); iObj++)
	{
		m_FbxObj[iObj].Release();
	}
	return true;
}
Sample::Sample()
{

}
Sample::~Sample()
{}


RUN();