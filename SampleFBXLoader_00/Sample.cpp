﻿#include "Sample.h"

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
	m_FbxObj.Init();
	//m_FbxObj.Load("../../data/fbx/SM_Barrel.fbx");
	//m_FbxObj.Load("../../data/fbx/SM_Rock.fbx");
	//m_FbxObj.Load("../../data/fbx/MultiCameras.fbx");
	//m_FbxObj.Load("../../data/fbx/st00sc00.fbx");
	//m_FbxObj.Load("../../data/fbx/SM_Tree_Var01.fbx");
	m_FbxObj.Load("../../data/fbx/Turret_Deploy1/Turret_Deploy1.fbx");


	JTexture* pTex = I_Texture.Load(L"../../data/ui/main_start_nor.png");
	JShader* pVShader = I_Shader.CreateVertexShader(
		m_pd3dDevice.Get(), L"Box.hlsl", "VS");
	JShader* pPShader = I_Shader.CreatePixelShader(
		m_pd3dDevice.Get(), L"Box.hlsl", "PS");
	for (int iObj = 0; iObj < m_FbxObj.m_DrawList.size(); iObj++)
	{
		m_FbxObj.m_DrawList[iObj]->Init();
		m_FbxObj.m_DrawList[iObj]->m_pColorTex = I_Texture.Load(m_FbxObj.m_DrawList[iObj]->m_szTexFileName);
		m_FbxObj.m_DrawList[iObj]->m_pVShader = pVShader;
		m_FbxObj.m_DrawList[iObj]->m_pPShader = pPShader;
		m_FbxObj.m_DrawList[iObj]->SetPosition(T::TVector3(0.0f, 1.0f, 0.0f));
		if (!m_FbxObj.m_DrawList[iObj]->Create(
			m_pd3dDevice.Get(),
			m_pImmediateContext.Get()))
		{
			return false;
		}
	}


	m_pMainCamera->CreateViewMatrix(T::TVector3(0, 25.0f, -50.0f),
		T::TVector3(0, 0.0f, 0));

	return true;
}
bool	Sample::Frame()
{
	for (int iObj = 0; iObj < m_FbxObj.m_TreeList.size(); iObj++)
	{
		T::TMatrix matLocal1 = m_FbxObj.m_TreeList[iObj]->m_matLocal;
		T::TMatrix matParent1;

		//부모의 로컬을 자식에게 곱한다. (부모가 이동을하면 그만큼 자식도 이동해야하기 때문)
		if (m_FbxObj.m_TreeList[iObj]->m_pParentObj != nullptr)
		{
			matParent1 = m_FbxObj.m_TreeList[iObj]->m_pParentObj->m_matLocal;
		}
		T::TMatrix matWorld1 = matLocal1 * matParent1;
		m_FbxObj.m_TreeList[iObj]->m_matAnim = matWorld1;		//draw와 노드의 주소를 공유하고 있기때문에 같이 적용된다.
	}
	return true;
}
bool	Sample::Render()
{
	for (int iObj = 0; iObj < m_FbxObj.m_DrawList.size(); iObj++)
	{
		T::TVector3 vLight(cosf(g_fGameTimer) * 100.0f,
			100,
			sinf(g_fGameTimer) * 100.0f);

		T::D3DXVec3Normalize(&vLight, &vLight);
		vLight = vLight * -1.0f;
		m_FbxObj.m_DrawList[iObj]->m_LightConstantList.vLightDir.x = vLight.x;
		m_FbxObj.m_DrawList[iObj]->m_LightConstantList.vLightDir.y = vLight.y;
		m_FbxObj.m_DrawList[iObj]->m_LightConstantList.vLightDir.z = vLight.z;
		m_FbxObj.m_DrawList[iObj]->m_LightConstantList.vLightDir.w = 1.0f;
		//m_FbxObj.m_ObjList[iObj]->m_bAlphaBlend = false;
		/*m_pImmediateContext->OMSetDepthStencilState(
			TDxState::g_pDSSDepthEnableWriteDisable, 0x00);*/

			/*m_FbxObj.m_ObjList[iObj]->SetMatrix(
				&m_FbxObj.m_ObjList[iObj]->m_matWorld,
				&m_pMainCamera->m_matView,
				&m_pMainCamera->m_matProj);*/
		m_FbxObj.m_DrawList[iObj]->SetMatrix(
			&m_FbxObj.m_DrawList[iObj]->m_matAnim,
			&m_pMainCamera->m_matView,
			&m_pMainCamera->m_matProj);
		m_FbxObj.m_DrawList[iObj]->Render();
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
	m_FbxObj.Release();
	return true;
}
Sample::Sample()
{

}
Sample::~Sample()
{}


RUN();