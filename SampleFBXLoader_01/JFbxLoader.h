#pragma once

#include "JObject3D.h"
#include <fbxsdk.h>
struct JTrack
{
	UINT	iFrame;
	T::TMatrix matTrack;
};
class JFbxModel : public TObject3D
{
public:
	int		 m_iIndex = -1;
	TMatrix  m_matLocal;
	TMatrix  m_matAnim;
	FbxNode* m_pFbxParent = nullptr;
	FbxNode* m_pFbxNode = nullptr;
	TFbxModel* m_pParentObj = nullptr;
	std::wstring m_szTexFileName;
	// submaterial
	std::vector<std::wstring>  m_szTexFileList;
	using TSubVertex = std::vector<TVertex>;
	std::vector<TSubVertex>      m_pSubVertexList;
	std::vector<ID3D11Buffer*>   m_pVBList;
	std::vector<TTexture*>		 m_pTextureList;

	std::vector<TTrack>			m_AnimTrack;
public:
	virtual bool    SetVertexData() override;
	virtual bool	CreateVertexBuffer()override;
	virtual bool    SetIndexData() override;
	virtual bool	PostRender() override;
	virtual bool    Release() override;

};


struct JScene
{
	UINT iStart;
	UINT iEnd;
	UINT iFrameSpeed;
};

class JFbxImporter : public JObject3D
{

public:
	FbxManager* m_pFbxManager;
	FbxImporter* m_pFbxImporter;
	FbxScene* m_pFbxScene;
	FbxNode* m_pRootNode;
public:
	std::vector<JFbxObj*> m_DrawList;	//°ú°Å OBJ
	std::vector<JFbxObj*> m_TreeList;

	ID3D11Buffer* m_pBoneCB = nullptr;
public:
	bool Load(ID3D11Device* pd3dDevice, std::wstring filename);
	virtual bool Load(std::string filename);
	virtual void PreProcess(FbxNode* node, JFbxObj* fbxParent);
	virtual void ParseMesh(JFbxObj* pObject);
	std::string ParseMaterial(FbxSurfaceMaterial* pMtrl);

	void ReadTextureCoord(FbxMesh* pFbxMesh, FbxLayerElementUV* pUVSet,
		int vertexIndex, int uvIndex, FbxVector2& uv);

	FbxColor ReadColor(const FbxMesh* mesh, DWORD dwVertexColorCount,
		FbxLayerElementVertexColor* pVertexColorSet,
		DWORD dwDCCIndex, DWORD dwVertexIndex);

	FbxVector4 ReadNormal(const FbxMesh* mesh, int controlPointIndex, int vertexCounter);
	int GetSubMaterialIndex(int iPoly, FbxLayerElementMaterial* pMaterialSetList);
	T::TMatrix     DxConvertMatrix(T::TMatrix m);
	T::TMatrix     ConvertMatrix(FbxMatrix& m);
public:
	T::TMatrix     ConvertAMatrix(FbxAMatrix& m);
	void		ParseAnimation();
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
	virtual bool CreateConstantBuffer(ID3D11Device* pDevice);

};
