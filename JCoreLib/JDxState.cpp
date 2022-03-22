#include "JDxState.h"

ID3D11BlendState* JDxState::m_pAlphaBlend = nullptr;
ID3D11BlendState* JDxState::m_pAlphaBlendDisable = nullptr;
ID3D11SamplerState* JDxState::m_pSamplerState = nullptr;
ID3D11RasterizerState* JDxState::g_pRSNoneCullSolid = nullptr;
ID3D11RasterizerState* JDxState::g_pRSNoneCullWireFrame = nullptr;
ID3D11RasterizerState* JDxState::g_pRSBackCullSolid = nullptr;
ID3D11RasterizerState* JDxState::g_pRSBackCullWireFrame = nullptr;
ID3D11SamplerState* JDxState::m_pSSLinear = nullptr;
ID3D11SamplerState* JDxState::m_pSSPoint = nullptr;
ID3D11DepthStencilState* JDxState::g_pDSSDepthEnable = nullptr;
ID3D11DepthStencilState* JDxState::g_pDSSDepthDisable = nullptr;

bool JDxState::SetState(ID3D11Device* pd3dDevice)
{
	HRESULT hr;

	D3D11_BLEND_DESC  blenddesc;
	ZeroMemory(&blenddesc, sizeof(D3D11_BLEND_DESC));
	
	blenddesc.RenderTarget[0].BlendEnable = TRUE;
	blenddesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blenddesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blenddesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	
	blenddesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blenddesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blenddesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blenddesc.RenderTarget[0].RenderTargetWriteMask =
		D3D11_COLOR_WRITE_ENABLE_ALL;
	hr = pd3dDevice->CreateBlendState(&blenddesc, &m_pAlphaBlend);

	blenddesc.RenderTarget[0].BlendEnable = FALSE;
	hr = pd3dDevice->CreateBlendState(&blenddesc, &m_pAlphaBlendDisable);


	D3D11_SAMPLER_DESC sd;
	ZeroMemory(&sd, sizeof(D3D11_SAMPLER_DESC));
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.MinLOD = FLT_MAX;
	sd.MaxLOD = FLT_MIN;
	hr = pd3dDevice->CreateSamplerState(&sd, &m_pSSLinear);
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	hr = pd3dDevice->CreateSamplerState(&sd, &m_pSSPoint);

	D3D11_RASTERIZER_DESC rsDesc;
	ZeroMemory(&rsDesc, sizeof(rsDesc));
	rsDesc.DepthClipEnable = TRUE;
	rsDesc.FillMode = D3D11_FILL_SOLID;
	rsDesc.CullMode = D3D11_CULL_NONE;
	if (FAILED(hr = pd3dDevice->CreateRasterizerState(&rsDesc, &JDxState::g_pRSNoneCullSolid))) return hr;
	

	rsDesc.FillMode = D3D11_FILL_WIREFRAME;
	if (FAILED(hr = pd3dDevice->CreateRasterizerState(&rsDesc, &JDxState::g_pRSNoneCullWireFrame))) return hr;
	//back
	rsDesc.CullMode = D3D11_CULL_BACK;
	rsDesc.FillMode = D3D11_FILL_WIREFRAME;
	if (FAILED(hr = pd3dDevice->CreateRasterizerState(&rsDesc, &JDxState::g_pRSBackCullWireFrame))) return hr;
	
	rsDesc.FillMode = D3D11_FILL_WIREFRAME;
	if (FAILED(hr = pd3dDevice->CreateRasterizerState(&rsDesc, &JDxState::g_pRSBackCullSolid))) return hr;





	D3D11_DEPTH_STENCIL_DESC dsDescDepth;
	ZeroMemory(&dsDescDepth, sizeof(D3D11_DEPTH_STENCIL_DESC));
	dsDescDepth.DepthEnable = TRUE;
	dsDescDepth.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDescDepth.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	dsDescDepth.StencilEnable = FALSE;
	dsDescDepth.StencilReadMask = 1;
	dsDescDepth.StencilWriteMask = 1;
	dsDescDepth.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	dsDescDepth.FrontFace.StencilPassOp = D3D11_STENCIL_OP_INCR;
	dsDescDepth.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDescDepth.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;

	// 디폴트 값
	dsDescDepth.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	dsDescDepth.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsDescDepth.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDescDepth.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;

	if (FAILED(hr = pd3dDevice->CreateDepthStencilState(&dsDescDepth, &g_pDSSDepthEnable)))
	{
		return hr;
	}

	dsDescDepth.DepthEnable = false;
	if (FAILED(hr = pd3dDevice->CreateDepthStencilState(&dsDescDepth, &g_pDSSDepthDisable)))
	{
		return hr;
	}
	return true;
}
bool JDxState::Release()
{
	if (g_pRSNoneCullSolid) g_pRSNoneCullSolid->Release();
	if (g_pRSNoneCullWireFrame) g_pRSNoneCullWireFrame->Release();
	if (g_pDSSDepthEnable) g_pDSSDepthEnable->Release();
	if (g_pDSSDepthDisable) g_pDSSDepthDisable->Release();
	if (m_pAlphaBlend) m_pAlphaBlend->Release();
	if (m_pAlphaBlendDisable) m_pAlphaBlendDisable->Release();
	m_pAlphaBlend = nullptr;
	m_pAlphaBlendDisable = nullptr;

	if (m_pSSLinear)m_pSSLinear->Release();
	if (m_pSSPoint)m_pSSPoint->Release();
	return true;
}