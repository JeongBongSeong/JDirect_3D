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
	m_Camera.Init();

	JTexture* pTex = I_Texture.Load(L"../../data/ui/main_start_nor.png");
	JShader* pVShader = I_Shader.CreateVertexShader(
		m_pd3dDevice.Get(), L"Box.hlsl", "VS");
	JShader* pPShader = I_Shader.CreatePixelShader(
		m_pd3dDevice.Get(), L"Box.hlsl", "PS");

	m_MapObj.Init();
	m_MapObj.SetDevice(m_pd3dDevice.Get(), m_pImmediateContext.Get());
	m_MapObj.CreateHeightMap(L"../../data/map/129.jpg");
	m_MapObj.m_pColorTex = I_Texture.Load(L"../../data/map/023.jpg");
	m_MapObj.m_pVShader = pVShader;
	m_MapObj.m_pPShader = pPShader;
	//JMatrix matRotate, matScale;
	//matRotate.XRotate(DegreeToRadian(180));
	//matScale.Scale(10, 10.0f, 10.0f);
	//m_MapObj.m_matWorld = matScale * matRotate;

	// 정점개수 (2^n + 1)	예) 16+1 = 17
	m_MapObj.CreateMap(128 + 1, 128 + 1,1);
	if (!m_MapObj.Create(m_pd3dDevice.Get(), m_pImmediateContext.Get()))
	{
		return false;
	}

	m_PlayerObj.Init();
	m_PlayerObj.m_pColorTex = I_Texture.Load(L"../../data/charport.bmp");
	m_PlayerObj.m_pVShader = pVShader;
	m_PlayerObj.m_pPShader = pPShader;
	m_PlayerObj.SetPosition(JVector3(0.0f, 1.0f, 0.0f));
	if (!m_PlayerObj.Create(m_pd3dDevice.Get(), m_pImmediateContext.Get()))
	{
		return false;
	}


	m_SkyObj.Init();
	m_SkyObj.SetPosition(JVector3(0.0f, 0.0f, 0.0f));
	if (!m_SkyObj.Create(m_pd3dDevice.Get(),
		m_pImmediateContext.Get(),
		L"sky.hlsl",
		L"../../data/sky/xxx.bmp"))
	{
		return false;
	}

	// world
	//TMatrix matRotate, matScale, matTrans;
	//matRotate.ZRotate(g_fGameTimer);
	//matScale.Scale(cos(g_fGameTimer) * 0.5f + 0.5f, 1.0f, 1.0f);
	//matTrans.Translation(0,	cos(g_fGameTimer) * 0.5f + 0.5f, 0);
	return true;
}
bool	Sample::Frame()
{
	if (JInput::Get().GetKey('A') || JInput::Get().GetKey(VK_LEFT))
	{
		//m_PlayerObj.m_vPos.x -= g_fSecPerFrame * 10.0f;
		m_PlayerObj.m_vPos -= m_PlayerObj.m_vRight * g_fSecPerFrame * 10.0f;
	}
	if (JInput::Get().GetKey('D') || JInput::Get().GetKey(VK_RIGHT))
	{
		//m_PlayerObj.m_vPos.x += g_fSecPerFrame * 10.0f;
		m_PlayerObj.m_vPos += m_PlayerObj.m_vRight * g_fSecPerFrame * 10.0f;
	}
	if (JInput::Get().GetKey('W') || JInput::Get().GetKey(VK_UP))
	{
		//m_PlayerObj.m_vPos.z += g_fSecPerFrame * 10.0f;
		m_PlayerObj.m_vPos += m_PlayerObj.m_vLook * g_fSecPerFrame * 10.0f;
	}
	if (JInput::Get().GetKey('S') || JInput::Get().GetKey(VK_DOWN))
	{
		//m_PlayerObj.m_vPos.z -= g_fSecPerFrame * 10.0f;
		m_PlayerObj.m_vPos -= m_PlayerObj.m_vLook * g_fSecPerFrame * 10.0f;

	}
	if (JInput::Get().GetKey('R') || JInput::Get().GetKey(VK_UP))
	{
		m_PlayerObj.m_vPos.y += g_fSecPerFrame * 10.0f;
	}
	if (JInput::Get().GetKey('F') || JInput::Get().GetKey(VK_DOWN))
	{
		m_PlayerObj.m_vPos.y -= g_fSecPerFrame * 10.0f;
	}
	JMatrix matRotate;
	JMatrix matScale;
	static float fRadian = 0.0f;
	fRadian += (JInput::Get().m_ptDeltaMouse.x / (float)g_rtClient.right) * JBASIS_PI;
	matRotate.YRotate(fRadian);

	matScale.Scale(50, 50, 50);
	m_PlayerObj.m_matWorld = matScale * matRotate;

	m_PlayerObj.m_vPos.y = m_MapObj.GetHeight(m_PlayerObj.m_vPos.x, m_PlayerObj.m_vPos.z) + 50;
	m_PlayerObj.SetPosition(m_PlayerObj.m_vPos);

	m_Camera.m_vTarget = m_PlayerObj.m_vPos;
	//m_Camera.m_vCamera = m_PlayerObj.m_vPos + JVector3(0, 10.0f, -25.0f);

	float y = m_MapObj.GetHeight(m_Camera.m_vCamera.x, m_Camera.m_vCamera.z);
	m_Camera.m_vCamera = m_PlayerObj.m_vPos +
		m_PlayerObj.m_vLook * -1.0f * 10.0f +
		m_PlayerObj.m_vUp * 10.0f;


	m_Camera.Frame();
	m_MapObj.Frame();
	m_PlayerObj.Frame();
	return true;
}
bool	Sample::Render()
{

	m_SkyObj.m_matViewSky = m_Camera.m_matView;
	m_SkyObj.m_matViewSky._41 = 0;
	m_SkyObj.m_matViewSky._42 = 0;
	m_SkyObj.m_matViewSky._43 = 0;
	JMatrix matRotation, matScale;
	matScale.Scale(3000.0f, 3000.0f, 3000.0f);
	matRotation.YRotate(g_fGameTimer * 0.00f);
	m_SkyObj.m_matWorld = matScale * matRotation;
	m_SkyObj.SetMatrix(NULL, &m_SkyObj.m_matViewSky, &m_Camera.m_matProj);
	m_pImmediateContext->RSSetState(JDxState::g_pRSNoneCullSolid);
	m_pImmediateContext->PSSetSamplers(0, 1, &JDxState::m_pSSPoint);
	m_SkyObj.Render();


	m_pImmediateContext->PSSetSamplers(0, 1, &JDxState::m_pSSLinear);
	m_MapObj.SetMatrix(nullptr, &m_Camera.m_matView, &m_Camera.m_matProj);
	m_MapObj.Render();

	m_PlayerObj.SetMatrix(nullptr, &m_Camera.m_matView, &m_Camera.m_matProj);
	
	m_PlayerObj.Render();
	/*m_ObjB.SetMatrix(nullptr, &m_Camera.m_matView, &m_Camera.m_matProj);
	m_ObjB.Render();*/

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
	m_MapObj.Release();
	m_PlayerObj.Release();
	m_ObjB.Release();
	return true;
}
Sample::Sample()
{

}
Sample::~Sample()
{}


RUN();