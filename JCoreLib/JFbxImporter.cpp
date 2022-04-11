#define  _CRT_SECURE_NO_WARNINGS
#include "JFbxImporter.h"

T::TMatrix     JFbxImporter::DxConvertMatrix(T::TMatrix m)
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
T::TMatrix     JFbxImporter::ConvertMatrix(FbxMatrix& m)
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
T::TMatrix     JFbxImporter::ConvertAMatrix(FbxAMatrix& m)
{
	TMatrix mat;
	float* pMatArray = reinterpret_cast<float*>(&mat);
	double* pSrcArray = reinterpret_cast<double*>(&m);
	for (int i = 0; i < 16; i++)
	{
		pMatArray[i] = pSrcArray[i];
	}
	return mat;
}
void		JFbxImporter::ParseAnimation()
{
	FbxTime::SetGlobalTimeMode(FbxTime::eFrames30);
	FbxAnimStack* stack = m_pFbxScene->GetSrcObject<FbxAnimStack>(0);
	if (stack == nullptr) return;

	FbxString TakeName = stack->GetName();
	FbxTakeInfo* TakeInfo = m_pFbxScene->GetTakeInfo(TakeName);
	FbxTimeSpan LocalTimeSpan = TakeInfo->mLocalTimeSpan;
	FbxTime start = LocalTimeSpan.GetStart();
	FbxTime end = LocalTimeSpan.GetStop();
	FbxTime Duration = LocalTimeSpan.GetDuration();

	FbxTime::EMode TimeMode = FbxTime::GetGlobalTimeMode();
	FbxLongLong s = start.GetFrameCount(TimeMode);
	FbxLongLong n = end.GetFrameCount(TimeMode);
	m_Scene.iStart = s;
	m_Scene.iEnd = n;
	m_Scene.iFrameSpeed = 30;
	// 1�ʿ� 30 frame 
	// 1Frame = 160 Tick
	// 50 Frame 
	FbxTime time;
	JTrack tTrack;
	for (FbxLongLong t = s; t <= n; t++)
	{
		time.SetFrame(t, TimeMode);
		for (int iObj = 0; iObj < m_TreeList.size(); iObj++)
		{
			FbxAMatrix matGlobal = m_TreeList[iObj]->m_pFbxNode->EvaluateGlobalTransform(time);
			tTrack.iFrame = t;
			tTrack.matTrack = DxConvertMatrix(ConvertAMatrix(matGlobal));
			m_TreeList[iObj]->m_AnimTrack.push_back(tTrack);
		}
	}
}

//���� �θ��Ʈ   (ó������ rootNode�� nullptr(��Ʈ�̱⶧��)�� �޴´�.)
void    JFbxImporter::PreProcess(FbxNode* node, JFbxModel* fbxParent)
{
	JFbxModel* fbx = nullptr;
	if (node != nullptr)
	{
		fbx = new JFbxModel;					//Model ���� Ī�Ѵ�.
		fbx->m_pFbxParent = node->GetParent();	//�ش� ����� �θ� �� ���ο� fbx�� �ִ´�.
		fbx->m_pFbxNode = node;					//�ش� ��带 �ִ´�.
		fbx->m_csName = to_mw(node->GetName());	//�ش� ����� �̸��� ��´�.
		fbx->m_pParentObj = fbxParent;			//�ش� fbx�� �θ� fbx�� �ִ´�.  (�� ����� �θ� �����ϰ��ִ� JFbxObj�����̴�.)
		fbx->m_iIndex = m_TreeList.size();		//���� Ʈ������Ʈ�� ũ�� �� ������� ���� ��
		m_TreeList.push_back(fbx);
	}

	// camera, light, mesh, shape, animation
	FbxMesh* pMesh = node->GetMesh();
	if (pMesh)
	{
		m_DrawList.push_back(fbx);	//�޽� �����Ͱ� �����ϴ� ��� �ش� ����� Model����� �ּҸ� �����Ѵ�.
	}
	int iNumChild = node->GetChildCount();	// ����� �ڽ� Ȯ��
	for (int iNode = 0; iNode < iNumChild; iNode++) // �ڽ��� ����ŭ ��� ȣ��
	{
		FbxNode* child = node->GetChild(iNode);		//�ڽ� ������ ���� ����
		PreProcess(child, fbx);						//�ڽĳ���� �ּҿ� ������ ����Ǿ��ִ� Model��带 ���ڷ� ��� ȣ��
	}
}
bool JFbxImporter::Load(ID3D11Device* pd3dDevice, std::wstring filename)
{
	if (Load(to_wm(filename).c_str()))
	{
		CreateConstantBuffer(pd3dDevice);
		JShader* pVShader = I_Shader.CreateVertexShader(pd3dDevice, L"..\\..\\data\\Shader\\Box.hlsl", "VS");
		JShader* pPShader = I_Shader.CreatePixelShader(pd3dDevice, L"..\\..\\data\\Shader\\Box.hlsl", "PS");
		for (int iObj = 0; iObj < m_DrawList.size(); iObj++)
		{
			m_DrawList[iObj]->Init();
			m_DrawList[iObj]->m_pVShader = pVShader;
			m_DrawList[iObj]->m_pPShader = pPShader;
			if (!m_DrawList[iObj]->Create(pd3dDevice, m_pContext))
			{
				return false;
			}
		}
	}
	return true;
}
bool	JFbxImporter::Load(std::string filename)
{
	Init();
	bool bRet = m_pFbxImporter->Initialize(filename.c_str());
	bRet = m_pFbxImporter->Import(m_pFbxScene);
	m_pRootNode = m_pFbxScene->GetRootNode();
	PreProcess(m_pRootNode, nullptr);
	ParseAnimation();

	for (int iObj = 0; iObj < m_DrawList.size(); iObj++)
	{
		ParseMesh(m_DrawList[iObj]);
	}
	Release();
	return true;
}
void	JFbxImporter::ParseMesh(JFbxModel* pObject)
{
	FbxMesh* pFbxMesh = pObject->m_pFbxNode->GetMesh();
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
				tVertex.c.w = pObject->m_iIndex;


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
bool JFbxImporter::CreateConstantBuffer(ID3D11Device* pDevice)
{
	HRESULT hr;
	//gpu�޸𸮿� ���� �Ҵ�(���ϴ� �Ҵ� ũ��)
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.ByteWidth = sizeof(JBoneWorld);
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	//D3D11_SUBRESOURCE_DATA sd;
	//ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
	//sd.pSysMem = &m_matBoneArray;

	if (FAILED(hr = pDevice->CreateBuffer(&bd, NULL, &m_pBoneCB)))
	{
		return false;
	}
	return true;
}
bool	JFbxImporter::Init()
{
	m_pFbxManager = FbxManager::Create();
	m_pFbxImporter = FbxImporter::Create(m_pFbxManager, "");
	m_pFbxScene = FbxScene::Create(m_pFbxManager, "");
	return true;
}
bool	JFbxImporter::Frame()
{
	return true;
}
bool	JFbxImporter::Render()
{
	return true;
}
bool	JFbxImporter::Release()
{
	if (m_pBoneCB)m_pBoneCB->Release();
	m_pBoneCB = nullptr;
	for (int iObj = 0; iObj < m_DrawList.size(); iObj++)
	{
		m_DrawList[iObj]->Release();
	}
	if (m_pFbxScene)m_pFbxScene->Destroy();
	if (m_pFbxImporter)m_pFbxImporter->Destroy();
	if (m_pFbxManager)m_pFbxManager->Destroy();
	m_pFbxScene = nullptr;
	m_pFbxImporter = nullptr;
	m_pFbxManager = nullptr;
	return true;
}