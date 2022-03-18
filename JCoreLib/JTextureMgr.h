#pragma once
#include"JBaseMgr.h"
#include <d3dcompiler.h>
#include "DDSTextureLoader.h"
#include "WICTextureLoader.h"

class JTexture
{
public:
	int m_iIndex;
	std::wstring m_csName;
	std::wstring m_szMsg;
	TCHAR m_szBuffer[256];
	ComPtr<ID3D11Texture2D> m_pTexture;
	ComPtr<ID3D11ShaderResourceView> m_pSRV;
	D3D11_TEXTURE2D_DESC m_TextureDesc;
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
	bool	Load(ID3D11Device* pd3dDevice, std::wstring filename);
public:
	JTexture();
	virtual ~JTexture();
};

class JTextureMgr : public JBaseMgr<JTexture, JTextureMgr>
{
	friend class JSingleton<JTextureMgr>;
private:
	JTextureMgr();
public:
	virtual ~JTextureMgr();
};

#define I_Texture JTextureMgr::Get()