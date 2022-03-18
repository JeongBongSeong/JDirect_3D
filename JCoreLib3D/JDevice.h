#pragma once
#include "JWindow.h"

class JDevice : public JWindow
{
public:
	ComPtr<ID3D11Device> m_pd3dDevice;
	//ID3D11Device* m_pd3dDevice;// 디바이스 객체
	ComPtr<IDXGISwapChain> m_pSwapChain;
	//IDXGISwapChain* m_pSwapChain;// 스왑체인 객체
	ComPtr<ID3D11RenderTargetView> m_pRenderTargetView;
	//ID3D11RenderTargetView* m_pRenderTargetView;// 메인 랜더타켓 뷰 //여러개의 백버퍼가 있을 때 어느 버퍼를 뿌릴 걸지 결정하는 것
	ComPtr<IDXGIFactory> m_pGIFactory;
	//IDXGIFactory* m_pGIFactory;
	ComPtr<ID3D11DeviceContext> m_pImmediateContext;
	//ID3D11DeviceContext* m_pImmediateContext;// 다비이스 컨텍스트 객체

	DXGI_SWAP_CHAIN_DESC	m_SwapChainDesc;	// 스왑체인 속성값
	D3D11_VIEWPORT m_ViewPort;// 뷰 포트 속성값
	D3D_DRIVER_TYPE m_driverType;
	D3D_DRIVER_TYPE m_DriverType;
	D3D_FEATURE_LEVEL m_FeatureLevel;	// Direct3D 특성레벨 속성값	
	// 스왑체인 속성값
public:
	virtual HRESULT InitDeivice();
	virtual bool	CreateDevice();
	virtual bool	CreateRenderTargetView();
	virtual bool	SetViewport();
	virtual bool	CleapupDevice();
public:
	void			ResizeDevice(UINT iWidth, UINT iHeight);
public:
	JDevice();
	virtual ~JDevice();
};