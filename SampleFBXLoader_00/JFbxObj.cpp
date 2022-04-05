#include "JFbxLoader.h"

bool    JFbxObj::SetVertexData()
{
	// 서브 정점 리스트가 존재하면 실행
	if (m_pSubVertexList.size() > 0)
	{
		//버텍스 버퍼 초기화
		m_pVBList.resize(m_pSubVertexList.size());
	}
	return true;
}
bool	JFbxObj::CreateVertexBuffer()
{
	if (m_pSubVertexList.size() <= 0) return false;
	HRESULT hr;
	for(int iMtrl = 0; iMtrl < m_pSubVertexList.size(); iMtrl++)
	{

		if (m_pSubVertexList[iMtrl].size() <= 0) continue;

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
		bd.ByteWidth = sizeof(JVertex) * m_pSubVertexList[iMtrl].size();
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
		sd.pSysMem = &m_pSubVertexList[iMtrl].at(0);

		if (FAILED(hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pVBList[iMtrl])))
		{
			return false;
		}
		
	}
	return true;
}
bool    JFbxObj::SetIndexData()
{
	return true;
}
bool	JFbxObj::PostRender()
{
	UINT StartSlot;
	UINT NumBuffers;
	UINT Strides = sizeof(JVertex);
	UINT Offsets = 0;

	for (int iMtrl = 0; iMtrl < m_pSubVertexList.size(); iMtrl++)
	{
		if (m_pTextureList.size() > 0 &&
			m_pTextureList[iMtrl] != nullptr)
		{
			// 텍스처리스트의 iMtrl번째에 SRV를 넘긴다.
			m_pContext->PSSetShaderResources(0, 1,
				m_pTextureList[iMtrl]->m_pSRV.GetAddressOf());
		}

		m_pContext->IASetVertexBuffers(0,1,
			&m_pVBList[iMtrl],&Strides,&Offsets);

		if (m_IndexList.size() <= 0)
		{
			m_pContext->Draw(m_pSubVertexList[iMtrl].size(), 0);
		}
		else
		{
			m_pContext->DrawIndexed(m_IndexList.size(), 0, 0);
		}
	}
	return true;
}
bool    JFbxObj::Release()
{
	JObject3D::Release();
	for (int ivb = 0; ivb < m_pVBList.size(); ivb++)
	{
		if (m_pVBList[ivb] != nullptr)
		{
			m_pVBList[ivb]->Release();
		}
	}
	return true;
}