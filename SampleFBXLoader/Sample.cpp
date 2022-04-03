#include "Sample.h"
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
	//m_FbxObj.Load("../../data/fbx/MultiCameras.FBX");
	//m_FbxObj.Load("../../data/fbx/st00sc00.fbx");
	m_FbxObj.Load("../../data/fbx/SM_Tree_Var01.fbx");

	JTexture* pTex = I_Texture.Load(L"../../data/ui/main_start_nor.png");
	JShader* pVShader = I_Shader.CreateVertexShader(
		m_pd3dDevice.Get(), L"Box.hlsl", "VS");
	JShader* pPShader = I_Shader.CreatePixelShader(
		m_pd3dDevice.Get(), L"Box.hlsl", "PS");

	
	for (int iObj = 0; iObj < m_FbxObj.m_ObjList.size(); iObj++)
	{
		m_FbxObj.m_ObjList[iObj]->Init();
		m_FbxObj.m_ObjList[iObj]->m_pColorTex = I_Texture.Load(m_FbxObj.m_ObjList[iObj]->m_szTexFileName);
		m_FbxObj.m_ObjList[iObj]->m_pVShader = pVShader;
		m_FbxObj.m_ObjList[iObj]->m_pPShader = pPShader;
		m_FbxObj.m_ObjList[iObj]->SetPosition(T::TVector3(0.0f, 1.0f, 0.0f));
		if (!m_FbxObj.m_ObjList[iObj]->Create(
			m_pd3dDevice.Get(),
			m_pImmediateContext.Get()))
		{
			return false;
		}
	}

	//m_SkyObj.Init();
	//m_SkyObj.SetPosition(T::TVector3(0.0f, 0.0f, 0.0f));
	//if (!m_SkyObj.Create(m_pd3dDevice.Get(),
	//	m_pImmediateContext.Get(),
	//	L"sky.hlsl",
	//	L"../../data/sky/LobbyCube.dds"))
	//{
	//	return false;
	//}

	m_pMainCamera->CreateViewMatrix(T::TVector3(0, 25.0f, -50.0f),
		T::TVector3(0, 0.0f, 0));

	return true;
}
bool	Sample::Frame()
{

	return true;
}
bool	Sample::Render()
{
	//
	//m_SkyObj.m_matViewSky = m_pMainCamera->m_matView;
	//m_SkyObj.m_matViewSky._41 = 0;
	//m_SkyObj.m_matViewSky._42 = 0;
	//m_SkyObj.m_matViewSky._43 = 0;
	//T::TMatrix matRotation, matScale;
	//T::D3DXMatrixScaling(&matScale, 10.0f, 10.0f, 10.0f);
	//T::D3DXMatrixRotationY(&matRotation, g_fGameTimer * 0.00f);
	//m_SkyObj.m_matWorld = matScale * matRotation;
	//m_SkyObj.SetMatrix(NULL, &m_SkyObj.m_matViewSky, &m_pMainCamera->m_matProj);
	//m_pImmediateContext->RSSetState(JDxState::g_pRSNoneCullSolid);
	//m_pImmediateContext->PSSetSamplers(0, 1, &JDxState::m_pSSLinear);
	//m_pImmediateContext->PSSetSamplers(1, 1, &JDxState::m_pSSPoint);
	//m_SkyObj.Render();

	//if (m_bWireFrame)
	//{
	//	m_pImmediateContext->RSSetState(JDxState::g_pRSNoneCullSolid);
	//}
	//else
	//{
	//	m_pImmediateContext->RSSetState(JDxState::g_pRSNoneCullWireFrame);
	//}

	for (int iObj = 0; iObj < m_FbxObj.m_ObjList.size(); iObj++)
	{
		T::TVector3 vLight(cosf(g_fGameTimer) * 100.0f,
			100,
			sinf(g_fGameTimer) * 100.0f);

		T::D3DXVec3Normalize(&vLight, &vLight);
		vLight = vLight * -1.0f;
		m_FbxObj.m_ObjList[iObj]->m_LightConstantList.vLightDir.x = vLight.x;
		m_FbxObj.m_ObjList[iObj]->m_LightConstantList.vLightDir.y = vLight.y;
		m_FbxObj.m_ObjList[iObj]->m_LightConstantList.vLightDir.z = vLight.z;
		m_FbxObj.m_ObjList[iObj]->m_LightConstantList.vLightDir.w = 1.0f;
		//m_FbxObj.m_ObjList[iObj]->m_bAlphaBlend = false;
		/*m_pImmediateContext->OMSetDepthStencilState(
			TDxState::g_pDSSDepthEnableWriteDisable, 0x00);*/

		m_FbxObj.m_ObjList[iObj]->SetMatrix(nullptr,
			&m_pMainCamera->m_matView,
			&m_pMainCamera->m_matProj);
		m_FbxObj.m_ObjList[iObj]->Render();
	}

	m_pMainCamera->Render();
	

	std::wstring msg = L"FPS:";
	msg += std::to_wstring(m_GameTimer.m_iFPS);
	msg += L"  GT:";
	msg += std::to_wstring(m_GameTimer.m_fTimer);
	m_dxWrite.Draw(msg, g_rtClient, D2D1::ColorF(0, 0, 1, 1));
	return true;
}
bool	Sample::Release()
{
	//m_SkyObj.Release();
	m_FbxObj.Release();
	return true;
}
Sample::Sample()
{

}
Sample::~Sample()
{}


RUN();