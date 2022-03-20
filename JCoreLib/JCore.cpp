﻿#include "JCore.h"
#include "JObjectMgr.h"
#include "JSoundMgr.h"
bool	JCore::CoreInit()
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
	Init();

	return true;
}
bool	JCore::GameRun()
{
	CoreInit();
	while (WinRun())
	{
		CoreFrame();
		CoreRender();
	}
	CoreRelease();

	MemoryReporting();
	return true;
}
bool	JCore::CoreFrame()
{
	m_GameTimer.Frame();
	JInput::Get().Frame();
	I_ObjectMgr.Frame();
	I_Sound.Frame();
	Frame();
	m_dxWrite.Frame();
	return true;
}
bool	JCore::CoreRender()
{
	float color[4] = { 0.1543f, 0.23421f, 0.4323f,1.0f };
	//float color[4] = { 1, 0, 0,1.0f };
	m_pImmediateContext->ClearRenderTargetView(
		m_pRenderTargetView.Get(),
		color);
	m_pImmediateContext->ClearDepthStencilView(
		m_pDepthStencilView.Get(),
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	m_pImmediateContext->OMSetRenderTargets(1,
		m_pRenderTargetView.GetAddressOf(),
		m_pDepthStencilView.Get());

	m_pImmediateContext->PSSetSamplers(0, 1, &JDxState::m_pSamplerState);
	m_pImmediateContext->OMSetDepthStencilState(JDxState::g_pDSSDepthEnable, 0x00);
	m_pImmediateContext->RSSetState(JDxState::g_pRSBackCullSolid);

	Render();

	m_GameTimer.Render();
	JInput::Get().Render();

	m_dxWrite.Render();
	m_pSwapChain->Present(0, 0);
	return true;
}

bool	JCore::CoreRelease()
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