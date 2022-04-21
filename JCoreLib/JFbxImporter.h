#pragma once

#include "JObject3D.h"
#include <fbxsdk.h>

struct PNCT
{
	T::TVector3 p;
	T::TVector3 n;
	T::TVector4 c;
	T::TVector2 t;
};
struct JVertexIW
{
	float i[4];
	float w[4];
	JVertexIW()
	{
		i[0] = i[1] = i[2] = i[3] = 0;
		w[0] = w[1] = w[2] = w[3] = 0.0f;
	}
};


struct JTrack
{
	UINT	iFrame;
	T::TMatrix matTrack;
};

struct JWeight
{
	std::vector<int> Index;
	std::vector<float> Weight;
	void InsertWeight(int iBoneIndex, float fBoneWeight)
	{
		for (DWORD i = 0; i < Index.size(); ++i)
		{
			if (fBoneWeight > Weight[i])
			{
				for (DWORD j = (Index.size() - 1); j > i; --j)
				{
					Index[j] = Index[j - 1];
					Weight[j] = Weight[j - 1];
				}
				Index[i] = iBoneIndex;
				Weight[i] = fBoneWeight;
			}
		}
	}
	JWeight()
	{
		Index.resize(8);
		Weight.resize(8);
	}
};

class JFbxModel : public JObject3D
{
public:
	int m_iIndex = -1;
	bool m_bSkinned = false;
	T::TMatrix  m_matLocal;
	T::TMatrix  m_matAnim;
	FbxNode* m_pFbxParent = nullptr;
	FbxNode* m_pFbxNode = nullptr;
	JFbxModel* m_pParentObj = nullptr;
	std::vector<std::wstring> m_szTexFileNameList;
	// submaterial
	std::wstring  m_szTexFileName;
	using JSubVertex = std::vector<JVertex>;
	using JSubVertexIW = std::vector<JVertexIW>;

	std::vector<JSubVertex>      m_pSubVertexList;
	std::vector<JSubVertexIW>    m_pSubIWVertexList;
	std::vector<JWeight>		 m_WeightList;

	std::vector<ID3D11Buffer*>   m_pVBList;
	std::vector<ID3D11Buffer*>   m_pVBWeightList;

	std::vector<JTexture*>		 m_pTextureList;

	std::vector<JTrack>			m_AnimTrack;
	std::map<int, T::TMatrix> m_dxMatrixBindPoseMap;
public:
	virtual bool    SetVertexData() override;
	virtual bool	CreateVertexBuffer()override;
	virtual bool    SetIndexData() override;
	virtual bool	CreateInputLayout() override;
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

	std::map<int, T::TMatrix> m_dxMatrixBindPoseMap;
	std::map<FbxNode*, int> m_pFbxNodeMap;

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
	bool ParseMeshSkinning(FbxMesh* pFbxMesh, JFbxModel* pObject);
public:
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
