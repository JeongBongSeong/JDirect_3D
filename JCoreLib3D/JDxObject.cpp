#include "JDxObject.h"
#include "JObjectMgr.h"
void JDxObject::SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext)
{
	m_pd3dDevice = pd3dDevice;
	m_pContext = pContext;
}

bool JDxObject::LoadTexture(const TCHAR* szColorFileName, const TCHAR* szMaskFileName)
{
	m_pColorTex = I_Texture.Load(szColorFileName);
	if (szMaskFileName != nullptr)
	{
		m_pMaskTex = I_Texture.Load(szMaskFileName);
	}

	m_TextureDesc = m_pColorTex->m_TextureDesc;

	return true;
}


bool    JDxObject::SetVertexData()
{
	return true;
}

bool    JDxObject::SetIndexData()
{
	return true;
}

bool    JDxObject::SetConstantData()
{
	ZeroMemory(&m_ConstantList, sizeof(JConstantData));
	m_ConstantList.Color.x = 1.0f;
	m_ConstantList.Color.y = 1.0f;
	m_ConstantList.Color.z = 1.0f;
	m_ConstantList.Color.w = 1.0f;
	m_ConstantList.Timer.x = 0.0f;
	m_ConstantList.Timer.y = 1.0f;
	m_ConstantList.Timer.z = 0.0f;
	m_ConstantList.Timer.w = 0.0f;
	return true;
}

bool JDxObject::CreateVertexShader(const TCHAR* szFile)
{
	// 텍스트파일 쉐이더 사용
	m_pVShader = I_Shader.CreateVertexShader(m_pd3dDevice, szFile, "VS");

	return true;

}
bool JDxObject::CreatePixelShader(const TCHAR* szFile)
{
	m_pPShader = I_Shader.CreatePixelShader(m_pd3dDevice, szFile, "PS");
	return true;
}
bool JDxObject::CreateVertexBuffer()
{
	HRESULT hr = S_OK;
	D3D11_BUFFER_DESC bd;
	{
		ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
		bd.ByteWidth = sizeof(SimpleVertex) * m_VertexList.size();		//이 크기에 메모리를 1
		bd.Usage = D3D11_USAGE_DEFAULT;				//GPU에 할당한다.    3
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	//버텍스 버퍼용으로  2
	}
	D3D11_SUBRESOURCE_DATA sd;
	{
		ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
		sd.pSysMem = &m_VertexList.at(0);
	}

	if (FAILED(hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pVertexBuffer)))	//할당과 데이터를 같이 넣겟다.!
	{
		return false;
	}
	return true;
}

bool JDxObject::CreateIndexBuffer()
{
	HRESULT hr;
	if (m_IndexList.size() <= 0) return true;
	//gpu메모리에 버퍼 할당(원하는 할당 크기)
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.ByteWidth = sizeof(DWORD) * m_IndexList.size();
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
	sd.pSysMem = &m_IndexList.at(0);

	if (FAILED(hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pIndexBuffer)))
	{
		return false;
	}
	return true;
}

bool	JDxObject::CreateConstantBuffer()
{
	HRESULT hr;
	//gpu메모리에 버퍼 할당(원하는 할당 크기)
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.ByteWidth = sizeof(JConstantData);
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
	sd.pSysMem = &m_ConstantList;

	if (FAILED(hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pConstantBuffer)))
	{
		return false;
	}
	return true;
}

bool JDxObject::CreateInputLayout()
{
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD",0, DXGI_FORMAT_R32G32_FLOAT, 0,8,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		//{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	UINT numLayout = sizeof(layout) / sizeof(layout[0]);
	HRESULT hr = m_pd3dDevice->CreateInputLayout(layout, numLayout,
		m_pVShader->m_pVSCodeResult->GetBufferPointer(),
		m_pVShader->m_pVSCodeResult->GetBufferSize(),
		&m_pVertexLayout);

	if (FAILED(hr)) return false;
	return true;
}

bool JDxObject::Create(ID3D11Device* pd3dDevice,	ID3D11DeviceContext* pContext, const TCHAR* szShaderFileName, const TCHAR* szColorFileName, const TCHAR* szMaskFileName)
{

	HRESULT hr;
	/*m_rtCollision = JRect(m_vPos, m_fWidth, m_fHeight);
	I_ObjectMgr.AddCollisionExecute(this, std::bind(&JBaseObject::HitOverlap,this,std::placeholders::_1, std::placeholders::_2));

	I_ObjectMgr.AddSelectExecute(this, std::bind(&JBaseObject::HitSelect, this, std::placeholders::_1, std::placeholders::_2));*/

	SetDevice(pd3dDevice, pContext);

	if (szColorFileName != nullptr && !LoadTexture(szColorFileName, szMaskFileName))
	{
		return false;
	}
	if (!SetVertexData())
	{
		return false;
	}
	if (!SetIndexData())
	{
		return false;
	}
	if (!SetConstantData())
	{
		return false;
	}
	if (!CreateVertexBuffer())
	{
		return false;
	}
	if (!CreateIndexBuffer())
	{
		return false;
	}
	if (!CreateConstantBuffer())
	{
		return false;
	}
	if (szShaderFileName != nullptr && !CreateVertexShader(szShaderFileName))
	{
		return false;
	}
	if (szShaderFileName != nullptr && !CreatePixelShader(szShaderFileName))
	{
		return false;
	}
	if (!CreateInputLayout())
	{
		return false;
	}

	return true;
}
bool	JDxObject::Init()
{
	return true;
}
bool	JDxObject::Frame()
{
	/*int iNum = 10;
	m_VertexList[0].v.x += m_fSpeed*iNum;
	m_VertexList[1].v.x += m_fSpeed*iNum;
	m_VertexList[2].v.x += m_fSpeed*iNum;
	m_VertexList[3].v.x += m_fSpeed*iNum;
	m_VertexList[4].v.x += m_fSpeed*iNum;
	m_VertexList[5].v.x += m_fSpeed*iNum;
	m_pContext->UpdateSubresource(
		m_pVertexBuffer, 0, NULL, &m_VertexList.at(0), 0, 0);
		*/
	return true;
}
bool	JDxObject::Render()
{
	if (m_pColorTex != nullptr)
	{
		m_pContext->PSSetShaderResources(0, 1, m_pColorTex->m_pSRV.GetAddressOf());
	}
	if (m_pMaskTex != nullptr)
	{
		m_pContext->PSSetShaderResources(1, 1, m_pMaskTex->m_pSRV.GetAddressOf());
	}
	if (m_pVShader != nullptr)
	{
		m_pContext->VSSetShader(m_pVShader->m_pVertexShader, NULL, 0);
	}
	if (m_pPShader != nullptr)
	{
		m_pContext->PSSetShader(m_pPShader->m_pPixelShader, NULL, 0);
	}
	

	if (m_bAlphaBlend)
	{
		m_pContext->OMSetBlendState(JDxState::m_pAlphaBlend, 0, -1);
	}
	else 
	{
		m_pContext->OMSetBlendState(JDxState::m_pAlphaBlendDisable, 0, -1);
	}
	

	m_pContext->IASetInputLayout(m_pVertexLayout);
	
	
	UINT StartSlot = 0;
	UINT NumBuffers = 1;
	UINT pStrides = sizeof(SimpleVertex);
	UINT pOffsets = 0;
	// 1번째 인자 : 어느 그릇에 넣을것 이냐 ?
	// 2번째 인자 : 버텍스버퍼에 몇개있냐 ? 
	// 4번째 인자 : 하나의 정점의 크기
	// 5번째 인자 : 시작 값
	m_pContext->IASetVertexBuffers(StartSlot, NumBuffers, &m_pVertexBuffer, &pStrides, &pOffsets);
	m_pContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	m_pContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	m_pContext->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
	);
	if( m_IndexList.size() <= 0)
		m_pContext->Draw(m_VertexList.size(), 0);
	else
		m_pContext->DrawIndexed(m_IndexList.size(), 0, 0);

	return true;
}
bool JDxObject::Release()
{
	if (m_pVertexBuffer) m_pVertexBuffer->Release();
	if (m_pIndexBuffer) m_pIndexBuffer->Release();
	if (m_pConstantBuffer) m_pConstantBuffer->Release();
	if (m_pVertexLayout) m_pVertexLayout->Release();
	m_pVertexBuffer = nullptr;
	m_pIndexBuffer = nullptr;
	m_pConstantBuffer = nullptr;
	m_pVertexLayout = nullptr;

	return true;
}
JDxObject::JDxObject()
{
	m_fSpeed = 0.0001f;
}
JDxObject::~JDxObject() 
{
}

void JBaseObject::HitOverlap(JBaseObject* pObj, DWORD dwState)
{
	int k = 0;
}
void JBaseObject::HitSelect(JBaseObject* pObj, DWORD dwState)
{

}