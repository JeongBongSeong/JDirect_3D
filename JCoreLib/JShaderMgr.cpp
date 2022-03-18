#include "JShaderMgr.h"


bool JShader::Load(ID3D11Device* pd3dDevice, std::wstring filename)
{
	if (CreateVertexShader(pd3dDevice, filename))
	{
		return false;
	}
	if (CreatePixelShader(pd3dDevice, filename))
	{
		return false;
	}
	return true;
}

bool JShader::CreateVertexShader(ID3D11Device* pd3dDevice,std::wstring filename, std::string entry)
{
	// 텍스트파일 쉐이더 사용
	HRESULT hr = D3DCompileFromFile(filename.c_str(), nullptr, nullptr, entry.c_str(), "vs_5_0", 0, 0, &m_pVSCodeResult, &m_pErrorMsgs);
	if (FAILED(hr))
	{
		if (m_pErrorMsgs)
		{
			MessageBoxA(NULL, (char*)m_pErrorMsgs->GetBufferPointer(), "error", MB_OK);
			m_pErrorMsgs->Release();
		}
		return true;
	}

	hr = pd3dDevice->CreateVertexShader(m_pVSCodeResult->GetBufferPointer(), m_pVSCodeResult->GetBufferSize(), NULL, &m_pVertexShader);

	if (FAILED(hr)) return false;

	return true;

}

bool JShader::CreatePixelShader(ID3D11Device* pd3dDevice, std::wstring filename, std::string entry)
{
	// 텍스트파일 쉐이더 사용
	HRESULT hr = D3DCompileFromFile(filename.c_str(), nullptr, nullptr, entry.c_str(), "ps_5_0", 0, 0, &m_pPSCodeResult, &m_pErrorMsgs);
	if (FAILED(hr))
	{
		if (m_pErrorMsgs)
		{
			MessageBoxA(NULL, (char*)m_pErrorMsgs->GetBufferPointer(), "error", MB_OK);
			m_pErrorMsgs->Release();
		}
		return false;
	}

	hr = pd3dDevice->CreatePixelShader(m_pPSCodeResult->GetBufferPointer(), m_pPSCodeResult->GetBufferSize(), NULL, &m_pPixelShader);

	if (FAILED(hr)) return false;

	return true;
}

bool JShader::Init()
{
	return true;
}

bool JShader::Frame()
{
	return true;
}

bool JShader::Render()
{
	return true;
}

bool JShader::Release()
{
	if (m_pVertexShader) m_pVertexShader->Release();
	if (m_pPixelShader) m_pPixelShader->Release();
	m_pVertexShader = nullptr;
	m_pPixelShader = nullptr;
	return true;
}


JShader::JShader()
{
}
JShader::~JShader()
{
}

JShader* JShaderMgr::CreateVertexShader(ID3D11Device* pd3dDevice,
	std::wstring filename, std::string entry)
{
	std::wstring name = Splitpath(filename, to_mw(entry));
	JShader* pData = GetPtr(name);
	if (pData != nullptr)
	{
		return pData;
	}
	std::shared_ptr<JShader> pNewData = std::make_shared<JShader>();
	if (!pNewData->CreateVertexShader(pd3dDevice, filename, entry))
	{
		return nullptr;
	}
	pNewData->m_csName = name;
	pNewData->m_iIndex = m_iIndex;
	m_list.insert(make_pair(pNewData->m_csName, pNewData));
	m_iIndex++;
	return pNewData.get();
}
JShader* JShaderMgr::CreatePixelShader(ID3D11Device* pd3dDevice,
	std::wstring filename, std::string entry)
{
	std::wstring name = Splitpath(filename, to_mw(entry));
	JShader* pData = GetPtr(name);
	if (pData != nullptr)
	{
		return pData;
	}

	std::shared_ptr<JShader> pNewData = std::make_shared<JShader>();
	if (!pNewData->CreatePixelShader(pd3dDevice, filename, entry))
	{
		return nullptr;
	}
	pNewData->m_csName = name;
	m_list.insert(make_pair(pNewData->m_csName, pNewData));
	m_iIndex++;
	return pNewData.get();
}

JShaderMgr::JShaderMgr()
{
	m_iIndex = 0;
}

JShaderMgr::~JShaderMgr()
{
	Release();
}

