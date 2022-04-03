#include "JCore.h"
#include "JObjectMgr.h"
#include "JSoundMgr.h"
T::TVector4   g_fBackGroundColor;

bool JCore::CoreInit()
{
    m_GameTimer.Init();
    JInput::Get().Init();


  
    if (SUCCEEDED(InitDeivice()))
    {
        I_Shader.Set(m_pd3dDevice.Get());
        I_Texture.Set(m_pd3dDevice.Get());
        JDxState::SetState(m_pd3dDevice.Get());

        if (m_dxWrite.Init())
        {
            IDXGISurface1* pSurface = nullptr;
            HRESULT hr = m_pSwapChain->GetBuffer(0,
                __uuidof(IDXGISurface1),
                (void**)&pSurface);
            if (SUCCEEDED(hr))
            {
                m_dxWrite.SetRenderTarget(pSurface);
            }
            if (pSurface) pSurface->Release();
        }
    }

    {
        m_DefaultCamera.Init();

        m_DefaultCamera.CreateViewMatrix(T::TVector3(0, 300.0f, -100.0f),
            T::TVector3(0, 0.0f, 0));
        m_DefaultCamera.CreateProjMatrix(XM_PI * 0.25f,
            (float)g_rtClient.right / (float)g_rtClient.bottom, 0.1f, 10000.0f);
        m_DefaultCamera.m_pVShader = I_Shader.CreateVertexShader(
            m_pd3dDevice.Get(), L"D:/Study/Code/JDirect_3D/JCoreLib/Box.hlsl", "VSColor");
        m_DefaultCamera.m_pPShader = I_Shader.CreatePixelShader(
            m_pd3dDevice.Get(), L"D:/Study/Code/JDirect_3D/JCoreLib/Box.hlsl", "PSColor");
        m_DefaultCamera.SetPosition(T::TVector3(0.0f, 1.0f, 0.0f));
        if (!m_DefaultCamera.Create(m_pd3dDevice.Get(), m_pImmediateContext.Get()))
        {
            return false;
        }
        m_pMainCamera = &m_DefaultCamera;
    }
    Init();

    return true;
}

bool JCore::GameRun()
{
    // 
    CoreInit();
    //
    while (WinRun())
    {
        CoreFrame();
        CoreRender();
    }
    CoreRelease();

    MemoryReporting();
    return true;
}


bool JCore::CoreFrame()
{
    if (JInput::Get().GetKey(VK_F2) == KEY_PUSH)
    {
        m_bWireFrame = !m_bWireFrame;
    }
    if (JInput::Get().GetKey(VK_F3) == KEY_PUSH)
    {
        m_bBack = !m_bBack;
    }
    m_GameTimer.Frame();
    JInput::Get().Frame();
    m_pMainCamera->Frame();
    I_ObjectMgr.Frame();
    I_Sound.Frame();
    Frame();
    m_dxWrite.Frame();
    return true;
}

bool JCore::CoreRender()
{
    /*m_fColor[0] = g_fBackGroundColor.x;
    m_fColor[1] = g_fBackGroundColor.y;
    m_fColor[2] = g_fBackGroundColor.z;
    m_fColor[3] = g_fBackGroundColor.w;*/
    float color[4] = { 0.1543f, 0.23421f, 0.4323f,1.0f };
    m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView.Get(), color);
    m_pImmediateContext->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    m_pImmediateContext->OMSetRenderTargets(1, m_pRenderTargetView.GetAddressOf(), m_pDepthStencilView.Get());

    m_pImmediateContext->PSSetSamplers(0, 1, &JDxState::m_pSSLinear);
    m_pImmediateContext->PSSetSamplers(1, 1, &JDxState::m_pSSPoint);

    m_pImmediateContext->OMSetDepthStencilState(JDxState::g_pDSSDepthEnable, 0x00);
    
    if (m_bWireFrame)
    {
        m_pImmediateContext->RSSetState(JDxState::g_pRSBackCullSolid);
    }
    else
    {
        m_pImmediateContext->RSSetState(JDxState::g_pRSBackCullWireFrame);
    }

    Render();
    m_GameTimer.Render();
    JInput::Get().Render();
    m_dxWrite.Render();
    m_pSwapChain->Present(0, 0);

    return true;
}

bool JCore::CoreRelease()
{
    Release(); 
    JDxState::Release();
    m_dxWrite.Release();
    m_GameTimer.Release();
    JInput::Get().Release();
    CleapupDevice();
    return true;
}

void     JCore::ResizeDevice(UINT iWidth, UINT iHeight)
{
    if (m_pd3dDevice == nullptr) return;
    DeleteResizeDevice(iWidth, iHeight);

    m_dxWrite.DeleteDeviceResize();

    JDevice::ResizeDevice(iWidth, iHeight);

    IDXGISurface1* pSurface = nullptr;
    HRESULT hr = m_pSwapChain->GetBuffer(0,
        __uuidof(IDXGISurface1),
        (void**)&pSurface);
    if (SUCCEEDED(hr))
    {
        m_dxWrite.SetRenderTarget(pSurface);
    }
    if (pSurface) pSurface->Release();

    CreateResizeDevice(iWidth, iHeight);
}

JCore::JCore()
{
}

JCore::~JCore()
{
}

