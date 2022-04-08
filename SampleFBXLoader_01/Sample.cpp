#include "Sample.h"

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



	std::vector<std::string> listname;
	listname.push_back("../../data/fbx/SM_Barrel.fbx");
	listname.push_back("../../data/fbx/SM_Rock.fbx");
	listname.push_back("../../data/fbx/MultiCameras.fbx");
	listname.push_back("../../data/fbx/st00sc00.fbx");
	listname.push_back("../../data/fbx/SM_Tree_Var01.fbx");
	listname.push_back("../../data/fbx/Turret_Deploy1/Turret_Deploy1.fbx");
	//listname.push_back("../../data/fbx/Man.fbx");

	I_ObjectMgr.Set(m_pd3dDevice.Get(), m_pImmediateContext.Get());
	m_FbxObj.resize(listname.size());

	for(int iObj1=0; iObj1 < listname.size(); iObj1++)
	{
		JFbxImporter* fbx = &m_FbxObj[iObj1];
		fbx->m_pd3dDevice = m_pd3dDevice.Get();
		fbx->m_pContext = m_pImmediateContext.Get();
		fbx->m_pImporter = I_ObjectMgr.Load(listname[iObj]);
		fbx->m_DrawList.resize(fbx->m_pImporter->m_DrawList.size());
		fbx->SetPosition(T::TVector3(iObj1 * 100.0f, 0, 0));
		fbx->Init();
		//fbx->Load(listname[iObj1]);
		//fbx->CreateConstantBuffer(m_pd3dDevice.Get());
		//JShader* pVShader = I_Shader.CreateVertexShader(
		//	m_pd3dDevice.Get(), L"..\\..\\data\\shader\\Box.hlsl", "VS");
		//JShader* pPShader = I_Shader.CreatePixelShader(
		//	m_pd3dDevice.Get(), L"..\\..\\data\\shader\\Box.hlsl", "PS");
		for (int iDraw = 0; iDraw < fbx->m_pImporter->m_DrawList.size(); iDraw++)
		{
			pFbx->m_pImporter->m_DrawList[iDraw]->m_pContext = m_pImmediateContext.Get();
			/*
			fbx->m_DrawList[iObj2]->Init();
			fbx->m_DrawList[iObj2]->m_pColorTex = I_Texture.Load(fbx->m_DrawList[iObj2]->m_szTexFileName);
			fbx->m_DrawList[iObj2]->m_pVShader = pVShader;
			fbx->m_DrawList[iObj2]->m_pPShader = pPShader;*/
			//test += T::TVector3(10.0f, 0.0f, 0.0f);
			//fbx->m_DrawList[iObj2]->SetPosition(test);
			/*if (!fbx->m_DrawList[iObj2]->Create(
				m_pd3dDevice.Get(),
				m_pImmediateContext.Get()))
			{
				return false;
			}*/
		}
	}

	m_pMainCamera->CreateViewMatrix(T::TVector3(0, 25.0f, -50.0f),
		T::TVector3(0, 0.0f, 0));

	return true;
}
bool	Sample::Frame()
{
	
	for (int iObj = 0; iObj <m_FbxObj.size(); iObj++)
	{
		//JFbxImporter* fbx = &m_FbxObj[iObj];
		//fbx->m_fTime += g_fSecPerFrame * fbx->m_Scene.iFrameSpeed * fbx->m_fDir * 1.0f;
		//if (fbx->m_fTime >= fbx->m_pFbxScene.iEnd)
		//{
		//	fbx->m_fDir *= -1.0f;
		//}
		//if (fbx->m_fTime <= fbx->m_pFbxScene.iStart)
		//{
		//	fbx->m_fDir *= -1.0f;
		//}
		//int iFrame = fbx->m_fTime;
		//iFrame = max(0, min(fbx->m_pFbxScene.iEnd, iFrame));
		//
		//for (int iObj2 = 0; iObj2 < fbx->m_TreeList.size(); iObj2++)
		//{
		//	JFbxObj* pObject = fbx->m_TreeList[iObj2];
		//	if (pObject->m_AnimTrack.size() > 0)
		//	{
		//		fbx->m_TreeList[iObj2]->m_matAnim = pObject->m_AnimTrack[iFrame].matTrack;
		//	}
		//	if(pObject->m_AnimTrack.size() > 0)
		//	{
		//		fbx->m_matBoneArray.matBoneWorld[iObj2] = pObject->m_AnimTrack[iFrame].matTrack;
		//	}
		//	T::D3DXMatrixTranspose(
		//		&fbx->m_matBoneArray.matBoneWorld[iObj2],
		//		&fbx->m_matBoneArray.matBoneWorld[iObj2]);
		//}
		////업데이트 상수 버퍼 (Bone)
		//m_pImmediateContext.Get()->UpdateSubresource(fbx->m_pBoneCB, 0, NULL, &fbx->m_matBoneArray, 0, 0);


		m_FbxObj[iObj].Frame();
	}
	return true;
}
bool	Sample::Render()
{
	for (int iObj = 0; iObj < m_FbxObj.size(); iObj++)
	{
		//JFbxImporter* fbx = &m_FbxObj[iObj1];
		//m_pImmediateContext.Get()->VSSetConstantBuffers(
		//	2, 1, &fbx->m_pBoneCB
		//);
		//for (int iObj2 = 0; iObj2 < fbx->m_DrawList.size(); iObj2++)
		//{
		//	JFbxObj* pFpxObj = fbx->m_DrawList[iObj2];
		//	T::TVector3 vLight(cosf(g_fGameTimer) * 100.0f,
		//		100,
		//		sinf(g_fGameTimer) * 100.0f);

		//	T::D3DXVec3Normalize(&vLight, &vLight);
		//	vLight = vLight * -1.0f;
		//	pFpxObj->m_LightConstantList.vLightDir.x = vLight.x;
		//	pFpxObj->m_LightConstantList.vLightDir.y = vLight.y;
		//	pFpxObj->m_LightConstantList.vLightDir.z = vLight.z;
		//	pFpxObj->m_LightConstantList.vLightDir.w = 1.0f;
		//	//m_FbxObj.m_DrawList[iObj]->m_bAlphaBlend = false;
		//	/*m_pImmediateContext->OMSetDepthStencilState(
		//		TDxState::g_pDSSDepthEnableWriteDisable, 0x00);*/

		//		/*m_FbxObj.m_DrawList[iObj]->SetMatrix(
		//			&m_FbxObj.m_DrawList[iObj]->m_matWorld,
		//			&m_pMainCamera->m_matView,
		//			&m_pMainCamera->m_matProj);*/

		m_FbxObj[iObj].SetMatrix(nullptr, &m_pMainCamera->m_matView,	&m_pMainCamera->m_matProj);
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
		/*JFbxImporter* fbx = &m_FbxObj[iObj1];
		for (int iObj2 = 0; iObj2 < fbx->m_DrawList.size(); iObj2++)
		{
			fbx->m_DrawList[iObj2]->Release();
		}*/
	}
	return true;
}
Sample::Sample()
{

}
Sample::~Sample()
{}


RUN();