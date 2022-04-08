#pragma once

#include "JObject3D.h"
#include <fbxsdk.h>
struct JTrack
{
	UINT	iFrame;
	T::TMatrix matTrack;
};
class JFbxModel : public JObject3D
{
public:
	int		 m_iIndex = -1;
	T::TMatrix  m_matLocal;
	T::TMatrix  m_matAnim;
	FbxNode* m_pFbxParent = nullptr;
	FbxNode* m_pFbxNode = nullptr;
	JFbxModel* m_pParentObj = nullptr;
	std::vector<std::wstring> m_szTexFileNameList;
	// submaterial
	std::wstring  m_szTexFileName;
	using TSubVertex = std::vector<JVertex>;
	std::vector<TSubVertex>      m_pSubVertexList;
	std::vector<ID3D11Buffer*>   m_pVBList;
	std::vector<JTexture*>		 m_pTextureList;

	std::vector<JTrack>			m_AnimTrack;
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
	JScene		m_Scene;
	float m_fDir = 1.0f;
	float m_fTime = 0.0f;
	float m_fSpeed = 1.0f;
	JBoneWorld	  m_matBoneArray;
public:
	FbxManager* m_pFbxManager;
	FbxImporter* m_pFbxImporter;
	FbxScene* m_pFbxScene;
	FbxNode* m_pRootNode;
public:
	std::vector<JFbxModel*> m_DrawList;	//°ú°Å OBJ
	std::vector<JFbxModel*> m_TreeList;

	ID3D11Buffer* m_pBoneCB = nullptr;
public:
	bool Load(ID3D11Device* pd3dDevice, std::wstring filename);
	virtual bool Load(std::string filename);
	virtual void PreProcess(FbxNode* node, JFbxModel* fbxParent = nullptr);
	virtual void ParseMesh(JFbxModel* pObject);
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
