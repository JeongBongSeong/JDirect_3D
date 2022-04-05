#pragma once

#include "JObject3D.h"
#include <fbxsdk.h>

class JFbxObj : public JObject3D
{
public:
	T::TMatrix m_matLocal;
	T::TMatrix m_matAnim;
	int	m_iIndex = 1;
public:
	FbxNode* m_pFbxParent = nullptr;
	FbxNode* m_pFbxNode = nullptr;
	JFbxObj* m_pParentObj = nullptr;
	std::wstring m_szTexFileName;

	// subMaterial
	std::vector<std::wstring> m_szTexFileNameList;
	using JSubVertex = std::vector<JVertex>;
	std::vector<JSubVertex>	m_pSubVertexList;
	std::vector<ID3D11Buffer*> m_pVBList;
	std::vector<JTexture*>	m_pTextureList;
public:
	virtual bool    SetVertexData() override;
	virtual bool	CreateVertexBuffer()override;
	virtual bool    SetIndexData() override;
	virtual bool	PostRender() override;
	virtual bool    Release() override;
};

class JFbxLoader : public JObject3D
{
public:
	FbxManager* m_pFbxManager;
	FbxImporter* m_pFbxImporter;
	FbxScene* m_pFbxScene;
	FbxNode* m_pRootNode;
public:
	std::vector<JFbxObj*> m_DrawList;	//°ú°Å OBJ
	std::vector<JFbxObj*> m_TreeList;
	

public:
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
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
};
