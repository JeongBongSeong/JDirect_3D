#include "JDxObject.h"

void JDxObject::SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext)
{
	m_pd3dDevice = pd3dDevice;
	m_pContext = pContext;
}

void JDxObject::Convert(JVector2 center, float fWidth, float fHeight, vector<SimpleVertex>& retList)
{
	// --      +-
	// -+      ++
	vector<SimpleVertex> list(6);
	float halfWidth = fWidth / 2.0f;
	float halfHeight = fHeight / 2.0f;
	list[0].v = { center.x - halfWidth, center.y - halfHeight };
	list[1].v = { center.x + halfWidth, center.y - halfHeight };
	list[2].v = { center.x - halfWidth, center.y + halfHeight };
	list[3].v = list[2].v;
	list[4].v = list[1].v;
	list[5].v = { center.x + halfWidth, center.y + halfHeight };

	Convert(list, retList);
}
void JDxObject::Convert(vector<SimpleVertex>& list, vector<SimpleVertex>& retList)
{
	retList.resize(list.size());
	for (int i = 0; i < list.size(); i++)
	{
		// 0 ~ 800 -> 0 ~ 1 -> -1 ~ +1
		retList[i].v.x = list[i].v.x / g_rtClient.right;
		retList[i].v.y = list[i].v.y / g_rtClient.bottom;
		// 0 ~ 1 -> -1 ~ +1 :::: -1 ~ +1 -> 0 ~ 1
		// x = x * 2 + -1;  ::::  x= x * 0.5f + 0.5f;
		retList[i].v.x = retList[i].v.x * 2.0f - 1.0f;
		retList[i].v.y = -1.0f * (retList[i].v.y * 2.0f - 1.0f);
	}
	retList[0].t.x = 0.0f; retList[0].t.y = 0.0f;
	retList[1].t.x = 1.0f; retList[1].t.y = 0.0f;
	retList[2].t.x = 0.0f; retList[2].t.y = 1.0f;
	retList[3].t = retList[2].t;
	retList[4].t = retList[1].t;
	retList[5].t.x = 1.0f; retList[5].t.y = 1.0f;
}

bool JDxObject::Create(ID3D11Device* pd3dDevice,	ID3D11DeviceContext* pContext, JVector2 vPos, float fWidth, float fHeight)
{
	SetDevice(pd3dDevice, pContext);
	
	HRESULT hr = S_OK;
	
	m_vPos = vPos;
	Convert(m_vPos, fWidth, fHeight, m_VertexList);

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
	// 텍스트파일 쉐이더 사용

	ID3DBlob* error = nullptr;
	hr = D3DCompileFromFile(
		L"VertexShader.txt",
		nullptr,
		nullptr,
		"VS",
		"vs_5_0",
		0,
		0,
		&m_pVSBlob,
		&m_pErrorMsgsBlob);
	if (FAILED(hr))
	{
		MessageBoxA(NULL,
			(char*)m_pErrorMsgsBlob->GetBufferPointer(),
			"error", MB_OK);
		if (m_pErrorMsgsBlob) m_pErrorMsgsBlob->Release();
		return false;
	}

	hr = m_pd3dDevice->CreateVertexShader(m_pVSBlob->GetBufferPointer(),
		m_pVSBlob->GetBufferSize(),
		NULL, &m_pVertexShader);

	if (FAILED(hr)) return false;

	hr = D3DCompileFromFile(
		L"PixelShader.txt",
		nullptr,
		nullptr,
		"PS",
		"ps_5_0",
		0,
		0,
		&m_pPSBlob,
		&m_pErrorMsgsBlob);
	if (FAILED(hr))
	{
		MessageBoxA(NULL,
			(char*)m_pErrorMsgsBlob->GetBufferPointer(),
			"error", MB_OK);
		if (m_pErrorMsgsBlob) m_pErrorMsgsBlob->Release();
		return false;
	}

	hr = m_pd3dDevice->CreatePixelShader(m_pPSBlob->GetBufferPointer(),
		m_pPSBlob->GetBufferSize(),
		NULL, &m_pPixelShader);
	if (FAILED(hr)) return false;

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD",0, DXGI_FORMAT_R32G32_FLOAT, 0,8,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		//{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	UINT numLayout = sizeof(layout) / sizeof(layout[0]);
	hr = m_pd3dDevice->CreateInputLayout(layout, numLayout,
		m_pVSBlob->GetBufferPointer(),
		m_pVSBlob->GetBufferSize(),
		&m_pVertexLayout);

	if (FAILED(hr)) return false;
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
	m_pContext->IASetInputLayout(m_pVertexLayout);
	m_pContext->VSSetShader(m_pVertexShader, NULL, 0);
	m_pContext->PSSetShader(m_pPixelShader, NULL, 0);
	
	UINT StartSlot = 0;
	UINT NumBuffers = 1;
	UINT pStrides = sizeof(SimpleVertex);
	UINT pOffsets = 0;
	// 1번째 인자 : 어느 그릇에 넣을것 이냐 ?
	// 2번째 인자 : 버텍스버퍼에 몇개있냐 ? 
	// 4번째 인자 : 하나의 정점의 크기
	// 5번째 인자 : 시작 값
	m_pContext->IASetVertexBuffers(StartSlot, NumBuffers, &m_pVertexBuffer, &pStrides, &pOffsets);
	m_pContext->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
	);
	m_pContext->Draw(m_VertexList.size(), 0);
	return true;
}
bool JDxObject::Release()
{
	if (m_pVertexBuffer) m_pVertexBuffer->Release();
	if (m_pVertexLayout) m_pVertexLayout->Release();
	if (m_pVertexShader) m_pVertexShader->Release();
	if (m_pPixelShader) m_pPixelShader->Release();
	if (m_pVSBlob) m_pVSBlob->Release();
	if (m_pPSBlob) m_pPSBlob->Release();
	m_pVertexBuffer = nullptr;
	m_pVertexLayout = nullptr;
	m_pVertexShader = nullptr;
	m_pPixelShader = nullptr;
	m_pVSBlob = nullptr;
	m_pPSBlob = nullptr;
	return true;
}
JDxObject::JDxObject()
{
	m_fSpeed = 0.00001f;
}
JDxObject::~JDxObject() {}