//#include "Sample.h"
//void	Sample::CreateResizeDevice(UINT iWidth, UINT iHeight)
//{
//	int k = 0;
//}
//void	Sample::DeleteResizeDevice(UINT iWidth, UINT iHeight)
//{
//	int k = 0;
//}
//bool	Sample::Init()
//{
//	m_FbxObj.Init();
//	m_FbxObj.Load("..\\..\\data\\fbx\\box.FBX");
//	JTexture* pTex = I_Texture.Load(L"../../data/ui/main_start_nor.png");
//	JShader* pVShader = I_Shader.CreateVertexShader(
//		m_pd3dDevice.Get(), L"D:/Study/Code/JDirect_3D/JCoreLib/Box.hlsl", "VS");
//	JShader* pPShader = I_Shader.CreatePixelShader(
//		m_pd3dDevice.Get(), L"D:/Study/Code/JDirect_3D/JCoreLib/Box.hlsl", "PS");
//	
//	m_SkyObj.Init();
//	m_SkyObj.SetPosition(T::TVector3(0.0f, 0.0f, 0.0f));
//	if (!m_SkyObj.Create(m_pd3dDevice.Get(),
//		m_pImmediateContext.Get(),
//		L"sky.hlsl",
//		L"../../data/sky/LobbyCube.dds"))
//	{
//		return false;
//	}
//
//
//	m_pMainCamera->CreateViewMatrix(T::TVector3(0, 25.0f, -50.0f),
//		T::TVector3(0, 0.0f, 0));
//	return true;
//}
//bool	Sample::Frame()
//{
//	T::TVector2 dir = JInput::Get().GetDelta();
//
//	if (JInput::Get().GetKey('A') || JInput::Get().GetKey(VK_LEFT))
//	{
//		m_pMainCamera->MoveSide(-g_fSecPerFrame * 1000.0f);
//	}
//	if (JInput::Get().GetKey('D') || JInput::Get().GetKey(VK_RIGHT))
//	{
//		m_pMainCamera->MoveSide(g_fSecPerFrame * 1000.0f);
//	}
//	//m_Camera.MoveLook(10.0f);
//	if (JInput::Get().GetKey('W') || JInput::Get().GetKey(VK_UP))
//	{
//		m_pMainCamera->MoveLook(g_fSecPerFrame * 1000.0f);
//	}
//	if (JInput::Get().GetKey('S') || JInput::Get().GetKey(VK_DOWN))
//	{
//		m_pMainCamera->MoveLook(-g_fSecPerFrame * 1000.0f);
//	}
//	m_pMainCamera->Update(T::TVector4(-dir.x, -dir.y, 0, 0));
//	m_pMainCamera->Frame();
//	m_SkyObj.Frame();
//	return true;
//}
//bool	Sample::Render()
//{
//	m_SkyObj.m_matViewSky = m_Camera.m_matView;
//	m_SkyObj.m_matViewSky._41 = 0;
//	m_SkyObj.m_matViewSky._42 = 0;
//	m_SkyObj.m_matViewSky._43 = 0;
//	T::TMatrix matRotation, matScale;
//	T::D3DXMatrixScaling(&matScale, 10.0f, 10.0f, 10.0f);
//	T::D3DXMatrixRotationY(&matRotation, g_fGameTimer * 0.00f);
//	m_SkyObj.m_matWorld = matScale * matRotation;
//	m_SkyObj.SetMatrix(NULL, &m_SkyObj.m_matViewSky, &m_Camera.m_matProj);
//	m_pImmediateContext->RSSetState(JDxState::g_pRSNoneCullSolid);
//	m_pImmediateContext->PSSetSamplers(0, 1, &JDxState::m_pSSLinear);
//	m_pImmediateContext->PSSetSamplers(1, 1, &JDxState::m_pSSPoint);
//	m_SkyObj.Render();
//	return true;
//}
//bool	Sample::Release()
//{
//	m_FbxObj.Release();
//	return true;
//}
//Sample::Sample()
//{
//
//}
//Sample::~Sample()
//{}
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
	JTexture* pTex = I_Texture.Load(L"../../data/ui/main_start_nor.png");
	JShader* pVShader = I_Shader.CreateVertexShader(
		m_pd3dDevice.Get(), L"D:/Study/Code/JDirect_3D/JCoreLib/Box.hlsl", "VS");
	JShader* pPShader = I_Shader.CreatePixelShader(
		m_pd3dDevice.Get(), L"D:/Study/Code/JDirect_3D/JCoreLib/Box.hlsl", "PS");

	//m_MapObj.Init();
	//m_MapObj.SetDevice(m_pd3dDevice.Get(), m_pImmediateContext.Get());
	//m_MapObj.CreateHeightMap(L"../../data/map/HEIGHT_MOUNTAIN.bmp");
	//m_MapObj.m_pColorTex = I_Texture.Load(L"../../data/map/020.bmp");
	//m_MapObj.m_pVShader = I_Shader.CreateVertexShader(
	//	m_pd3dDevice.Get(), L"map.hlsl", "VS");
	//m_MapObj.m_pPShader = I_Shader.CreatePixelShader(
	//	m_pd3dDevice.Get(), L"map.hlsl", "PS");

	//m_MapObj.CreateMap(m_MapObj.m_iNumCols, m_MapObj.m_iNumRows, 20.0f);
	//if (!m_MapObj.Create(m_pd3dDevice.Get(), m_pImmediateContext.Get()))
	//{
	//	return false;
	//}

	/*m_PlayerObj.Init();
	m_PlayerObj.m_pColorTex = I_Texture.Load(L"../../data/charport.bmp");
	m_PlayerObj.m_pVShader = pVShader;
	m_PlayerObj.m_pPShader = pPShader;
	m_PlayerObj.SetPosition(T::TVector3(0.0f, 1.0f, 0.0f));
	if (!m_PlayerObj.Create(m_pd3dDevice.Get(), m_pImmediateContext.Get()))
	{
		return false;
	}*/


	m_SkyObj.Init();
	m_SkyObj.SetPosition(T::TVector3(0.0f, 0.0f, 0.0f));
	if (!m_SkyObj.Create(m_pd3dDevice.Get(),
		m_pImmediateContext.Get(),
		L"sky.hlsl",
		L"../../data/sky/LobbyCube.dds"))
	{
		return false;
	}

	m_ObjList.resize(100);
	for (int iObj = 0; iObj < m_ObjList.size(); iObj++)
	{
		m_ObjList[iObj].Init();
		m_ObjList[iObj].m_pColorTex = I_Texture.Load(L"../../data/KGCABK.bmp");
		m_ObjList[iObj].m_pVShader = pVShader;
		m_ObjList[iObj].m_pPShader = pPShader;
		m_ObjList[iObj].SetPosition(
			T::TVector3(-300.0f + rand() % 600,
				100.0f,
				-300.0f + rand() % 600));
		if (!m_ObjList[iObj].Create(m_pd3dDevice.Get(),
			m_pImmediateContext.Get()))
		{
			return false;
		}
	}

	return true;
}
bool	Sample::Frame()
{

	m_MapObj.Frame();
	m_PlayerObj.Frame();
	m_pMainCamera->Frame();
	T::TMatrix matRotateObj;

	//오브젝트 회전 시 사용
	//T::TMatrix matRotate;
	T::TMatrix matScale;
	//T::D3DXMatrixRotationY(&matRotate, -dir.y);
	T::D3DXMatrixScaling(&matScale, 50, 50, 50);
	

	for (auto& obj : m_ObjList)
	{
		T::D3DXMatrixScaling(&matScale,
			10, 10, 10);
		/*	10 * cosf(g_fGameTimer),
			10 * cosf(g_fGameTimer),
			10 * cosf(g_fGameTimer));*/
		T::D3DXMatrixRotationYawPitchRoll(&matRotateObj,
			cosf(g_fGameTimer * obj.m_vPos.x * 0.001f) * XM_PI,
			sinf(g_fGameTimer * obj.m_vPos.y * 0.001f) * XM_PI,
			1.0f);
		obj.m_matWorld = matScale * matRotateObj;
		obj.m_vPos.y = 50;
		obj.SetPosition(obj.m_vPos);
		obj.Frame();
	}

	return true;
}
bool	Sample::Render()
{
	
	m_SkyObj.m_matViewSky = m_pMainCamera->m_matView;
	m_SkyObj.m_matViewSky._41 = 0;
	m_SkyObj.m_matViewSky._42 = 0;
	m_SkyObj.m_matViewSky._43 = 0;
	T::TMatrix matRotation, matScale;
	T::D3DXMatrixScaling(&matScale, 10.0f, 10.0f, 10.0f);
	T::D3DXMatrixRotationY(&matRotation, g_fGameTimer * 0.00f);
	m_SkyObj.m_matWorld = matScale * matRotation;
	m_SkyObj.SetMatrix(NULL, &m_SkyObj.m_matViewSky, &m_pMainCamera->m_matProj);
	m_pImmediateContext->RSSetState(JDxState::g_pRSNoneCullSolid);
	m_pImmediateContext->PSSetSamplers(0, 1, &JDxState::m_pSSLinear);
	m_pImmediateContext->PSSetSamplers(1, 1, &JDxState::m_pSSPoint);
	m_SkyObj.Render();

	if (m_bWireFrame)
	{
		m_pImmediateContext->RSSetState(JDxState::g_pRSNoneCullSolid);
	}
	else
	{
		m_pImmediateContext->RSSetState(JDxState::g_pRSNoneCullWireFrame);
	}
	//m_pImmediateContext->PSSetSamplers(0, 1, &JDxState::m_pSSLinear);
	//m_pImmediateContext->RSSetState(JDxState::g_pRSBackCullSolid);
	/*m_MapObj.SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	m_MapObj.Render();

	m_PlayerObj.SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	m_PlayerObj.Render();*/

	for (auto& obj : m_ObjList)
	{
		obj.SetMatrix(nullptr, &m_pMainCamera->m_matView,
			&m_pMainCamera->m_matProj);
		if (m_pMainCamera->ClassifyOBB(&obj.m_BoxCollision) == TRUE)
		{
			obj.Render();
		}
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
	m_SkyObj.Release();

	for (auto& obj : m_ObjList)
	{
		obj.Release();
	}
	return true;
}
Sample::Sample()
{

}
Sample::~Sample()
{}


RUN();