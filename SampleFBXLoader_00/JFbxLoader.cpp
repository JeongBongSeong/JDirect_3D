#define  _CRT_SECURE_NO_WARNINGS
#include "JFbxLoader.h"

T::TMatrix     JFbxLoader::DxConvertMatrix(T::TMatrix m)
{
	TMatrix mat;
	mat._11 = m._11; mat._12 = m._13; mat._13 = m._12;
	mat._21 = m._31; mat._22 = m._33; mat._23 = m._32;
	mat._31 = m._21; mat._32 = m._23; mat._33 = m._22;
	mat._41 = m._41; mat._42 = m._43; mat._43 = m._42;
	mat._14 = mat._24 = mat._34 = 0.0f;
	mat._44 = 1.0f;
	return mat;
}
T::TMatrix     JFbxLoader::ConvertMatrix(FbxMatrix& m)
{
	T::TMatrix mat;
	double* pSrcArray = reinterpret_cast<double*>(&m);
	float* pMatArray = reinterpret_cast<float*>(&mat);
	for (int i = 0; i < 16; i++)
	{
		pMatArray[i] = pSrcArray[i];
	}
	return mat;
}

//���� �θ��Ʈ   (ó������ rootNode�� nullptr(��Ʈ�̱⶧��)�� �޴´�.)
void    JFbxLoader::PreProcess(FbxNode* node, JFbxObj* fbxParent)
{
	JFbxObj* fbx = nullptr;
	if (node != nullptr)
	{
		fbx = new JFbxObj;
		fbx->m_pFbxParent = node->GetParent();	//�ش� ����� �θ� �� ���ο� fbx�� �ִ´�.
		fbx->m_pFbxNode = node;					//�ش� ��带 �ִ´�.
		fbx->m_csName = to_mw(node->GetName());	//�ش� ����� �̸��� ��´�.
		fbx->m_pParentObj = fbxParent;			//�ش� fbx�� �θ� fbx�� �ִ´�.  (�� ����� �θ� �����ϰ��ִ� JFbxObj�����̴�.)
		fbx->m_iIndex = m_TreeList.size();		//���� Ʈ������Ʈ�� ũ�� �� ������� ���� ��

		//����� srt�� �� ��ȯ�� �Ͽ� ���� ��Ŀ� �����Ѵ�.
		FbxVector4 scaleLcl = node->LclScaling.Get();
		FbxVector4 rotateLcl = node->LclRotation.Get();
		FbxVector4 transLcl = node->LclTranslation.Get();
		FbxMatrix matLocal(transLcl, rotateLcl, scaleLcl);
		//���� ���̱⿡ ����ȯ�� ������Ѵ�.
		//Fbx�� ��� 4x4���� 2��,3������ �ٲ㼭 �����ؾ��Ѵ�.
		fbx->m_matLocal = DxConvertMatrix(ConvertMatrix(matLocal));

		m_TreeList.push_back(fbx);
	}



	// camera, light, mesh, shape, animation
	FbxMesh* pMesh = node->GetMesh();
	if (pMesh)
	{
		m_DrawList.push_back(fbx);
	}
	int iNumChild = node->GetChildCount();
	for (int iNode = 0; iNode < iNumChild; iNode++)
	{
		FbxNode* child = node->GetChild(iNode);
		PreProcess(child, fbx);
	}
}
bool	JFbxLoader::Load(std::string filename)
{
	bool bRet = m_pFbxImporter->Initialize(filename.c_str());
	bRet = m_pFbxImporter->Import(m_pFbxScene);
	m_pRootNode = m_pFbxScene->GetRootNode();
	PreProcess(m_pRootNode, nullptr);

	for (int iObj = 0; iObj < m_DrawList.size(); iObj++)
	{
		ParseMesh(m_DrawList[iObj]);
	}
	return true;
}
void	JFbxLoader::ParseMesh(JFbxObj* pObject)
{
	FbxMesh* pFbxMesh = pObject->m_pFbxNode->GetMesh();
	if (pFbxMesh)
	{
		// �������(�ʱ� ���� ��ġ�� ��ȯ�� �� ���)
		// transform
		FbxAMatrix geom;
		FbxVector4 trans = pObject->m_pFbxNode->GetGeometricTranslation(FbxNode::eSourcePivot);
		FbxVector4 rot = pObject->m_pFbxNode->GetGeometricRotation(FbxNode::eSourcePivot);
		FbxVector4 scale = pObject->m_pFbxNode->GetGeometricScaling(FbxNode::eSourcePivot);
		geom.SetT(trans);
		geom.SetR(rot);
		geom.SetS(scale);

		FbxAMatrix normalMatrix = geom;
		normalMatrix = normalMatrix.Inverse();
		normalMatrix = normalMatrix.Transpose();

		// ���̾� ( 1���� ������, �������� ���ļ� ������ ����)
		std::vector<FbxLayerElementUV*> VertexUVSet;
		std::vector<FbxLayerElementVertexColor*> VertexColorSet;
		std::vector<FbxLayerElementMaterial*> MaterialSet;
		int iLayerCount = pFbxMesh->GetLayerCount();

		//���̾ ��� ���ǵ� �ع���(��ġ Pos)�� �����̴� 
		//�׷��⿡ Get�������ص� ���̾ �ٲ��� ������ ���� ���� ��µȴ�.
		for (int iLayer = 0; iLayer < iLayerCount; iLayer++)
		{
			FbxLayer* pFbxLayer = pFbxMesh->GetLayer(iLayer);
			if (pFbxLayer->GetUVs() != nullptr)
			{
				//�ؽ��� UV����Ʈ�̴�.
				VertexUVSet.push_back(pFbxLayer->GetUVs());
			}
			if (pFbxLayer->GetVertexColors() != nullptr)
			{
				//�����÷� ����Ʈ�̴�.
				VertexColorSet.push_back(pFbxLayer->GetVertexColors());
			}
			if (pFbxLayer->GetMaterials() != nullptr)
			{
				//���͸��� ����Ʈ�̴�.
				MaterialSet.push_back(pFbxLayer->GetMaterials());
			}
		}

		int iNumMtrl = pObject->m_pFbxNode->GetMaterialCount();
		for (int iMtrl = 0; iMtrl < iNumMtrl; iMtrl++)
		{
			FbxSurfaceMaterial* pSurface = pObject->m_pFbxNode->GetMaterial(iMtrl);
			if (pSurface)
			{
				std::string texturename = ParseMaterial(pSurface);
				std::wstring szTexFileName = L"../../data/fbx/";
				szTexFileName += to_mw(texturename);
				pObject->m_szTexFileNameList.push_back(szTexFileName);
				pObject->m_pTextureList.push_back(I_Texture.Load(szTexFileName));
			}
		}

		if (pObject->m_pTextureList.size() > 0)
		{
			pObject->m_szTexFileName = pObject->m_szTexFileNameList[0];
		}
		if (iNumMtrl > 0)
		{
			pObject->m_pSubVertexList.resize(iNumMtrl);
		}
		else
		{
			pObject->m_pSubVertexList.resize(1);
		}

		int iBasePolyIndex = 0;
		// �ﰢ��, �簢��
		int iNumPolyCount = pFbxMesh->GetPolygonCount();
		FbxVector4* pVertexPositions = pFbxMesh->GetControlPoints();
		int iNumFace = 0;
		for (int iPoly = 0; iPoly < iNumPolyCount; iPoly++)
		{
			int iPolySize = pFbxMesh->GetPolygonSize(iPoly);
			iNumFace = iPolySize - 2;

			int iSubMtrl = 0;
			if (iNumMtrl > 0 && MaterialSet[0] != nullptr)
			{
				iSubMtrl = GetSubMaterialIndex(iPoly, MaterialSet[0]);
			}
			for (int iFace = 0; iFace < iNumFace; iFace++)
			{
				// 1  2
				// 0  3
				// (max)021,032 ->  (dx)012, 023
				int VertexIndex[3] = { 0, iFace + 2, iFace + 1 };

				int CornerIndex[3];
				CornerIndex[0] = pFbxMesh->GetPolygonVertex(iPoly, VertexIndex[0]);
				CornerIndex[1] = pFbxMesh->GetPolygonVertex(iPoly, VertexIndex[1]);
				CornerIndex[2] = pFbxMesh->GetPolygonVertex(iPoly, VertexIndex[2]);
				for (int iIndex = 0; iIndex < 3; iIndex++)
				{
					JVertex tVertex;
					// Max(x,z,y) ->(dx)x,y,z    
					FbxVector4 v = pVertexPositions[CornerIndex[iIndex]];
					v = geom.MultT(v);
					tVertex.p.x = v.mData[0];
					tVertex.p.y = v.mData[2];
					tVertex.p.z = v.mData[1];

					// uv
					int u[3];
					u[0] = pFbxMesh->GetTextureUVIndex(iPoly, VertexIndex[0]);
					u[1] = pFbxMesh->GetTextureUVIndex(iPoly, VertexIndex[1]);
					u[2] = pFbxMesh->GetTextureUVIndex(iPoly, VertexIndex[2]);
					if (VertexUVSet.size() > 0)
					{
						FbxLayerElementUV* pUVSet = VertexUVSet[0];
						FbxVector2 uv;
						ReadTextureCoord(
							pFbxMesh,
							pUVSet,
							CornerIndex[iIndex],
							u[iIndex],
							uv);
						tVertex.t.x = uv.mData[0];
						tVertex.t.y = 1.0f - uv.mData[1];
					}

					FbxColor color = FbxColor(1, 1, 1, 1);
					if (VertexColorSet.size() > 0)
					{
						color = ReadColor(pFbxMesh,
							VertexColorSet.size(),
							VertexColorSet[0],
							CornerIndex[iIndex],
							iBasePolyIndex + VertexIndex[iIndex]);
					}
					tVertex.c.x = color.mRed;
					tVertex.c.y = color.mGreen;
					tVertex.c.z = color.mBlue;
					tVertex.c.w = 1;


					FbxVector4 normal = ReadNormal(pFbxMesh,
						CornerIndex[iIndex],
						iBasePolyIndex + VertexIndex[iIndex]);
					normal = normalMatrix.MultT(normal);
					tVertex.n.x = normal.mData[0]; // x
					tVertex.n.y = normal.mData[2]; // z
					tVertex.n.z = normal.mData[1]; // y

					//pObject->m_VertexList.push_back(tVertex);//36
					pObject->m_pSubVertexList[iSubMtrl].push_back(tVertex);
				}
			}

			iBasePolyIndex += iPolySize;
		}
	}
}
bool	JFbxLoader::Init()
{
	m_pFbxManager = FbxManager::Create();
	m_pFbxImporter = FbxImporter::Create(m_pFbxManager, "");
	m_pFbxScene = FbxScene::Create(m_pFbxManager, "");
	return true;
}
bool	JFbxLoader::Frame()
{
	return true;
}
bool	JFbxLoader::Render()
{
	return true;
}
bool	JFbxLoader::Release()
{
	for (int iObj = 0; iObj < m_DrawList.size(); iObj++)
	{
		m_DrawList[iObj]->Release();
	}
	m_pFbxScene->Destroy();
	m_pFbxImporter->Destroy();
	m_pFbxManager->Destroy();
	return true;
}