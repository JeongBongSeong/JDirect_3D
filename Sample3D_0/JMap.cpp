#include "JMap.h"
#include "WICTextureLoader.h"
bool JMap::Frame()
{
	JVector3 vLight(cosf(g_fGameTimer) * 100.0f,100,sinf(g_fGameTimer) * 100.0f);

	vLight = vLight.Normal() * -1.0f;
	m_ConstantList.Color.x = vLight.x;
	m_ConstantList.Color.y = vLight.y;
	m_ConstantList.Color.z = vLight.z;
	m_ConstantList.Color.w = 1.0f;
	return true;
}

bool JMap::CreateMap(UINT width, UINT height, float distance)
{
	//정점
	m_iNumCols = width;
	m_iNumRows = height;
	m_iNumCellRows = (height - 1);
	m_iNumCellCols = (width - 1);
	m_iNumFace = (height - 1)*(width - 1) *2;
	m_iCellDistance = distance;

	// 전체 정점의 개수
	m_iNumVertices = m_iNumCols * m_iNumRows;


	return false;
}

bool JMap::CreateHeightMap(std::wstring filename)
{

	HRESULT hr;
	ID3D11ShaderResourceView* pSRV = nullptr;
	ComPtr<ID3D11Resource> pTexture;
	size_t maxsize = 0;
	if (FAILED(hr = CreateWICTextureFromFileEx(m_pd3dDevice,
		filename.c_str(),
		maxsize,
		D3D11_USAGE_STAGING,
		0,
		D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ,
		0,
		DirectX::WIC_LOADER_DEFAULT,
		pTexture.GetAddressOf(), nullptr)))
	{
		return false;
	}
	ID3D11Texture2D* pTexture2D = NULL;
	if (FAILED(pTexture->QueryInterface(__uuidof(ID3D11Texture2D), (LPVOID*)&pTexture2D)))
	{
		return false;
	}

	D3D11_TEXTURE2D_DESC desc;
	pTexture2D->GetDesc(&desc);

	m_fHeightList.resize(desc.Height * desc.Width);

	if (pTexture2D)
	{
		D3D11_MAPPED_SUBRESOURCE MappedFaceDest;
		if (SUCCEEDED(m_pContext->Map((ID3D11Resource*)pTexture2D, D3D11CalcSubresource(0, 0, 1), D3D11_MAP_READ, 0, &MappedFaceDest)))
		{
			UCHAR* pTexels = (UCHAR*)MappedFaceDest.pData;
			JVertex	v;
			for (UINT row = 0; row < desc.Height; row++)
			{
				UINT rowStart = row * MappedFaceDest.RowPitch;
				for (UINT col = 0; col < desc.Width; col++)
				{
					UINT colStart = col * 4;
					UINT uRed = pTexels[rowStart + colStart + 0];
					m_fHeightList[row * desc.Width + col] = (float)uRed / 10;
				}
			}
			m_pContext->Unmap(pTexture2D, D3D11CalcSubresource(0, 0, 1));
		}
	}

	m_iNumRows = desc.Height;
	m_iNumCols = desc.Width;

	if (pTexture2D) pTexture2D->Release();
	return true;
	return false;
}

bool JMap::SetVertexData()
{
	//m_VertexList.resize(m_iNumVertices * 3);
	//float hHalfCol = m_iNumCols - 1 / 2.0f;
	//float hHalfRow = m_iNumRows - 1 / 2.0f;
	//float ftxOffset = ;
	//UINT iIndex = 0;
	//for (int iRow = 0; iRow < m_iNumRows; iRow++)
	//{
	//	for (int iCol = 0; iCol < m_iNumCols; iCol++)
	//	{
	//		int index = (iRow * m_iNumCols) + iCol;
	//		m_VertexList[index].p.x = ;
	//		m_VertexList[index].p.y = ;
	//		m_VertexList[index].p.z = ;
	//	}
	//}

	float hHalfCol = (m_iNumCols - 1) / 2.0f;
	float hHalfRow = (m_iNumRows - 1) / 2.0f;
	float  ftxOffetU = 1.0f / (m_iNumCols - 1);
	float  ftxOffetV = 1.0f / (m_iNumRows - 1);
	m_VertexList.resize(m_iNumVertices);

	UINT iIndex = 0;
	// 페이스 계산
	for (int iRow = 0; iRow < m_iNumRows; iRow++)
	{
		for (int iCol = 0; iCol < m_iNumCols; iCol++)
		{
			iIndex = (iRow*m_iNumCols)+ iCol;
			m_VertexList[iIndex].p.x = (iCol - hHalfCol)* m_iCellDistance;
			m_VertexList[iIndex].p.y = m_fHeightList[iIndex];
			m_VertexList[iIndex].p.z = -(iRow - hHalfRow)* m_iCellDistance;
			m_VertexList[iIndex].n = JVector3(0,1,0);
			m_VertexList[iIndex].c = JVector4(randstep(0.0f, 1.0f),randstep(0.0f, 1.0f),randstep(0.0f, 1.0f), 1);
			m_VertexList[iIndex].t = JVector2(ftxOffetU * iCol, ftxOffetV * iRow);
		}
	}


	return true;
}
bool		JMap::SetIndexData()
{
	//m_IndexList.push_back(0);
	m_IndexList.resize(m_iNumFace*3);
	UINT iIndex = 0;
	
	for (UINT iRow = 0; iRow < m_iNumCellRows; iRow++)
	{
		for (UINT iCol = 0; iCol < m_iNumCellCols; iCol++)
		{
			m_IndexList[iIndex+0] = (iRow * m_iNumCols) + iCol;
			m_IndexList[iIndex+1] = (iRow * m_iNumCols) + iCol+1;
			m_IndexList[iIndex+2] = ((iRow+1) * m_iNumCols) + iCol;
			
			m_IndexList[iIndex+3] = m_IndexList[iIndex + 2];
			m_IndexList[iIndex+4] = m_IndexList[iIndex + 1];
			m_IndexList[iIndex+5] = ((iRow + 1) * m_iNumCols) + iCol +1;

			// 페이스당 3개씩 소모하기 대문에 2번 총 6증가시킨다
			iIndex += 6;
		}
	}	

	// 6개씩 2개페이스의 노말 값과 정점들의 노말 값을 설정한다. 노말값을 설정 1셀달 2페이스

	iIndex = 0;
	JVector3 vLight(100, 100, 0);
	vLight = vLight.Normal() * 1.0f;
	for (UINT iRow = 0; iRow < m_iNumCellRows; iRow++)
	{
		for (UINT iCol = 0; iCol < m_iNumCellCols; iCol++)
		{
			JFace face;
			face.v0 = m_IndexList[iIndex + 0];
			face.v1 = m_IndexList[iIndex + 1];
			face.v2 = m_IndexList[iIndex + 2];
			JVector3 vNormal;
			JVector3  vE0 = (m_VertexList[face.v1].p - m_VertexList[face.v0].p).Normal();
			JVector3  vE1 = (m_VertexList[face.v2].p - m_VertexList[face.v0].p).Normal();

			face.vNormal = (vE0 ^ vE1).Normal();

			m_VertexList[face.v0].n += face.vNormal;
			m_VertexList[face.v1].n += face.vNormal;
			m_VertexList[face.v2].n += face.vNormal;

			float fDot = max(0.0f, vLight | face.vNormal);
			m_VertexList[face.v0].c = JVector4(fDot, fDot, fDot, 1);
			m_VertexList[face.v1].c = JVector4(fDot, fDot, fDot, 1);
			m_VertexList[face.v2].c = JVector4(fDot, fDot, fDot, 1);
			m_vFaceList.push_back(face);

			face.v0 = m_IndexList[iIndex + 3];
			face.v1 = m_IndexList[iIndex + 4];
			face.v2 = m_IndexList[iIndex + 5];
			
			vE0 = (m_VertexList[face.v0].p - m_VertexList[face.v2].p).Normal();
			vE1 = (m_VertexList[face.v1].p - m_VertexList[face.v2].p).Normal();

			vNormal = (vE0 ^ vE1).Normal();
			m_VertexList[face.v0].n += face.vNormal;
			m_VertexList[face.v1].n += face.vNormal;
			m_VertexList[face.v2].n += face.vNormal;

			fDot = max(0.0f, vLight | face.vNormal);
			m_VertexList[face.v0].c = JVector4(fDot, fDot, fDot, 1);
			m_VertexList[face.v1].c = JVector4(fDot, fDot, fDot, 1);
			m_VertexList[face.v2].c = JVector4(fDot, fDot, fDot, 1);
			m_vFaceList.push_back(face);

			iIndex += 6;
		}
	}
	for (int iRow = 0; iRow < m_iNumRows; iRow++)
	{
		for (int iCol = 0; iCol < m_iNumCols; iCol++)
		{
			m_VertexList[iRow * m_iNumCols + iCol].n.Normalize();
			float fDot = max(0.0f, vLight | m_VertexList[iRow * m_iNumCols + iCol].n);
			m_VertexList[iRow * m_iNumCols + iCol].c = JVector4(fDot, fDot, fDot, 1);
		}
	}

	return true;
}

JMap::JMap()
{

}
JMap::~JMap()
{

}