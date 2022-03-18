#pragma once
#include"JBaseMgr.h"

class JShader
{
public:
	int m_iIndex;
	std::wstring m_csName;
	std::wstring m_Msg;
	TCHAR m_szBuffer[256];
	ID3D11VertexShader* m_pVertexShader = nullptr;
	ID3D11PixelShader* m_pPixelShader = nullptr;
	ID3DBlob* m_pVSCodeResult = nullptr;
	ID3DBlob* m_pErrorMsgs = nullptr;
	ID3DBlob* m_pPSCodeResult = nullptr;
public:
	virtual bool CreateVertexShader(ID3D11Device* pd3dDevice, std::wstring filename, std::string entry = "VS");
	virtual bool CreatePixelShader(ID3D11Device* pd3dDevice, std::wstring filename, std::string entry = "PS");
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
	bool	Load(ID3D11Device* pd3dDevice, std::wstring filename);
public:
	JShader();
	virtual ~JShader();
};

class JShaderMgr : public JBaseMgr<JShader,JShaderMgr>
{
	friend class JSingleton<JShaderMgr>;
public:
	JShader* CreateVertexShader(ID3D11Device* pd3dDevice, std::wstring filename, std::string entry);
	JShader* CreatePixelShader(ID3D11Device* pd3dDevice, std::wstring filename, std::string entry);

private:
	JShaderMgr();
public:
	virtual ~JShaderMgr();
};


#define I_Shader JShaderMgr::Get()