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
	m_fCellDistance = distance;

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

float JMap::GetHeightMap(int row, int col)
{
	return m_VertexList[row * m_iNumRows + col].p.y;
}

float JMap::GetHeight(float fPosX, float fPosY)
{
	//해당 위치에 X 값을 찾아야한다.
	//해당 위치의 Z 값을 찾아야한다.
	// 2를 나누는 이유는 -2 ~ 2 이런식으로 저장되어 있기 때문이다.
	float fCellX = (float)((m_iNumCellCols * m_fCellDistance) / 2) + fPosX;
	float fCellZ = (float)((m_iNumCellRows * m_fCellDistance) / 2) + fPosY;
	//m_fHeightList[]

	fCellX /= (float)m_fCellDistance;
	fCellZ /= (float)m_fCellDistance;

	float fVertexCol = ::floorf(fCellX);
	float fVertexRow = ::floorf(fCellZ);

	// 높이맵 범위를 벗어나면 강제로 초기화 한다.
	if (fVertexCol < 0.0f)  fVertexCol = 0.0f;
	if (fVertexRow < 0.0f)  fVertexRow = 0.0f;
	if ((float)(m_iNumCols - 2) < fVertexCol)	fVertexCol = (float)(m_iNumCols - 2);
	if ((float)(m_iNumRows - 2) < fVertexRow)	fVertexRow = (float)(m_iNumRows - 2);
	float A = GetHeightMap((int)fVertexRow, (int)fVertexCol);
	float B = GetHeightMap((int)fVertexRow, (int)fVertexCol + 1);
	float C = GetHeightMap((int)fVertexRow + 1, (int)fVertexCol);
	float D = GetHeightMap((int)fVertexRow + 1, (int)fVertexCol + 1);

	// A정점의 위치에서 떨어진 값(변위값)을 계산한다. 0 ~ 1.0f
	float fDeltaX = fCellX - fVertexCol;
	float fDeltaZ = fCellZ - fVertexRow;
	// 보간작업를 위한 기준 페잇스를 찾는다. 
	float fHeight = 0.0f;
	// 윗페이스를 기준으로 보간한다.
	// fDeltaZ + fDeltaX < 1.0f
	if (fDeltaZ < (1.0f - fDeltaX))  //ABC
	{
		float uy = B - A; // A->B
		float vy = C - A; // A->C	
						  // 두 정점의 높이값의 차이를 비교하여 델타X의 값에 따라 보간값을 찾는다.		
		fHeight = A + Lerp(0.0f, uy, fDeltaX) + Lerp(0.0f, vy, fDeltaZ);
	}
	// 아래페이스를 기준으로 보간한다.
	else // DCB
	{
		float uy = C - D; // D->C
		float vy = B - D; // D->B
						  // 두 정점의 높이값의 차이를 비교하여 델타Z의 값에 따라 보간값을 찾는다.		
		fHeight = D + Lerp(0.0f, uy, 1.0f - fDeltaX) + Lerp(0.0f, vy, 1.0f - fDeltaZ);
	}
	return fHeight;

	return 0.0f;
}
float JMap::Lerp(float fStart, float fEnd, float fTangent)
{
	return fStart - (fStart * fTangent) + (fEnd * fTangent);
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
			m_VertexList[iIndex].p.x = (iCol - hHalfCol)* m_fCellDistance;
			m_VertexList[iIndex].p.y = m_fHeightList[iIndex];
			m_VertexList[iIndex].p.z = -(iRow - hHalfRow)* m_fCellDistance;
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