#pragma once
#include"JObject3D.h"

struct JFace
{
	UINT v0, v1, v2; // vb index;
	JVector3 vNormal; // vb index;
};

class JMap : public JObject3D
{
public:
	UINT m_iNumCols = 0;
	UINT m_iNumRows = 0;
	UINT m_iNumVertices = 0;
	UINT m_iNumCellCols = 0;
	UINT m_iNumCellRows = 0;
	UINT m_iNumFace = 0;
	float m_fCellDistance = 1.0f;
	std::vector<float>  m_fHeightList;
	std::vector<JFace> m_vFaceList;
public:
	virtual bool CreateMap(UINT width, UINT height, float distance);
	virtual bool CreateHeightMap(std::wstring filename);
	virtual float GetHeightMap(int row, int col);
	virtual float GetHeight(float fPosX, float fPosY);
	virtual float Lerp(float fStart, float fEnd, float fTangent);
	virtual bool SetVertexData();
	virtual bool SetIndexData();
public:
	virtual bool Frame() override;
public:
	JMap();
	virtual ~JMap();

};

