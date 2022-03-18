#include "JTextureMgr.h"

bool JTexture::Load(ID3D11Device* pd3dDevice, std::wstring filename)
{
	HRESULT hr = DirectX::CreateWICTextureFromFile(
		pd3dDevice,
		filename.c_str(),
		(ID3D11Resource**)m_pTexture.GetAddressOf(),
		m_pSRV.GetAddressOf()
	);
	if (FAILED(hr))
	{
		hr = DirectX::CreateDDSTextureFromFile(
			pd3dDevice,
			filename.c_str(),
			(ID3D11Resource**)m_pTexture.GetAddressOf(),
			m_pSRV.GetAddressOf()
		);
		if (FAILED(hr))
		{
			return false;
		}
	}
	m_pTexture->GetDesc(&m_TextureDesc);
	return true;
}

bool JTexture::Init()
{
	return true;
}

bool JTexture::Frame()
{
	return true;
}

bool JTexture::Render()
{
	return true;
}

bool JTexture::Release()
{
	return true;
}



JTexture::JTexture()
{

}

JTexture::~JTexture()
{
}

JTextureMgr::JTextureMgr()
{
	m_iIndex = 0;
}

JTextureMgr::~JTextureMgr()
{
	Release();
}
