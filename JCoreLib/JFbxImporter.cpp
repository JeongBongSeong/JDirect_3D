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
	// 1초에 30 frame 
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
			// 행렬분해
			// 행렬을 분해(SRT)
			T::D3DXMatrixDecompose(&tTrack.s, &tTrack.r, &tTrack.t, &tTrack.matTrack);
			m_TreeList[iObj]->m_AnimTrack.push_back(tTrack);
		}
	}
}

//노드와 부모노트   (처음에는 rootNode와 nullptr(루트이기때문)을 받는다.)
void    JFbxImporter::PreProcess(FbxNode* node, JFbxModel* fbxParent)
{
	JFbxModel* fbx = nullptr;
	if (node != nullptr)
	{
		fbx = new JFbxModel;					//Model 노드라 칭한다.
		fbx->m_pFbxParent = node->GetParent();	//해당 노드의 부모를 얻어서 새로운 fbx에 넣는다.
		fbx->m_pFbxNode = node;					//해당 노드를 넣는다.
		fbx->m_csName = to_mw(node->GetName());	//해당 노드의 이름을 얻는다.
		fbx->m_pParentObj = fbxParent;			//해당 fbx의 부모 fbx를 넣는다.  (위 노드의 부모를 저장하고있는 JFbxObj정보이다.)
		fbx->m_iIndex = m_TreeList.size();		//현재 트리리스트의 크기 즉 순서대로 들어온 값
		m_TreeList.push_back(fbx);
		m_pFbxNodeMap.insert(std::make_pair(node, fbx->m_iIndex));
		m_pFbxModelMap.insert(std::make_pair(fbx->m_csName, fbx));
	}

	// camera, light, mesh, shape, animation
	FbxMesh* pMesh = node->GetMesh();
	if (pMesh)
	{
		m_DrawList.push_back(fbx);	//메시 데이터가 존재하는 경우 해당 노드의 Model노드의 주소를 저장한다.
	}
	int iNumChild = node->GetChildCount();	// 노드의 자식 확인
	for (int iNode = 0; iNode < iNumChild; iNode++) // 자식의 수만큼 재귀 호출
	{
		FbxNode* child = node->GetChild(iNode);		//자식 포인터 변수 저장
		PreProcess(child, fbx);						//자식노드의 주소와 본인이 저장되어있는 Model노드를 인자로 재귀 호출
	}
}
bool JFbxImporter::Load(ID3D11Device* pd3dDevice, std::wstring filename)
{
	if (Load(to_wm(filename).c_str()))
	{
		CreateConstantBuffer(pd3dDevice);
		JShader* pVShader = I_Shader.CreateVertexShader(pd3dDevice, L"..\\..\\data\\Shader\\Character.hlsl", "VS");
		JShader* pPShader = I_Shader.CreatePixelShader(pd3dDevice, L"..\\..\\data\\Shader\\Character.hlsl", "PS");
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


bool JFbxImporter::ParseMeshSkinning(FbxMesh* pFbxMesh, JFbxModel* pObject)
{
	int iDeformerCount = pFbxMesh->GetDeformerCount(FbxDeformer::eSkin);
	if (iDeformerCount == 0)
	{
		return false;
	}
	// 정점의 개수와 동일
	int iVertexCount = pFbxMesh->GetControlPointsCount();
	pObject->m_WeightList.resize(iVertexCount);

	for (int dwDeformerIndex = 0; dwDeformerIndex < iDeformerCount; dwDeformerIndex++)
	{
		auto pSkin = reinterpret_cast<FbxSkin*>(pFbxMesh->GetDeformer(dwDeformerIndex, FbxDeformer::eSkin));
		DWORD dwClusterCount = pSkin->GetClusterCount();
		// dwClusterCount의 행렬이 전체 정점에 영향을 주었다.
		for (int dwClusterIndex = 0; dwClusterIndex < dwClusterCount; dwClusterIndex++)
		{
			auto pCluster = pSkin->GetCluster(dwClusterIndex);
			////
			FbxAMatrix matXBindPose;
			FbxAMatrix matReferenceGlobalInitPosition;
			pCluster->GetTransformLinkMatrix(matXBindPose);
			pCluster->GetTransformMatrix(matReferenceGlobalInitPosition);
			FbxMatrix matBindPose = matReferenceGlobalInitPosition.Inverse() * matXBindPose;

			T::TMatrix matInvBindPos = DxConvertMatrix(ConvertMatrix(matBindPose));
			matInvBindPos = matInvBindPos.Invert();
			int  iBoneIndex = m_pFbxNodeMap.find(pCluster->GetLink())->second;
			std::wstring name = m_TreeList[iBoneIndex]->m_csName;
			pObject->m_dxMatrixBindPoseMap.insert(make_pair(name, matInvBindPos));


			int dwClusterSize = pCluster->GetControlPointIndicesCount();

			// 영향을 받는 정점들의 인덱스
			int* pIndices = pCluster->GetControlPointIndices();
			double* pWeights = pCluster->GetControlPointWeights();
			// iBoneIndex의 영향을 받는 정점들이 dwClusterSize개 있다.
			for (int i = 0; i < dwClusterSize; i++)
			{
				// n번 정점(pIndices[i])은 iBoneIndex의 행렬에 
				// pWeights[i]의 가중치로 적용되었다.
				int iVertexIndex = pIndices[i];
				float fWeight = pWeights[i];
				pObject->m_WeightList[iVertexIndex].InsertWeight(iBoneIndex, fWeight);
			}
		}
	}

	return true;
}


void	JFbxImporter::ParseMesh(JFbxModel* pObject)
{
	FbxMesh* pFbxMesh = pObject->m_pFbxNode->GetMesh();
	pObject->m_bSkinned = ParseMeshSkinning(pFbxMesh, pObject);
	// 기하행렬(초기 정점 위치를 변환할 때 사용)
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

	// 레이어 ( 1번에 랜더링, 여러번에 걸쳐서 랜더링 개념)
	std::vector<FbxLayerElementUV*> VertexUVSet;
	std::vector<FbxLayerElementVertexColor*> VertexColorSet;
	std::vector<FbxLayerElementMaterial*> MaterialSet;
	int iLayerCount = pFbxMesh->GetLayerCount();

	//레이어가 몇개가 사용되든 밑바탕(위치 Pos)은 고정이다 
	//그렇기에 Get여러번해도 레이어가 바뀌지 않으면 같은 값이 출력된다.
	for (int iLayer = 0; iLayer < iLayerCount; iLayer++)
	{
		FbxLayer* pFbxLayer = pFbxMesh->GetLayer(iLayer);
		if (pFbxLayer->GetUVs() != nullptr)
		{
			//텍스쳐 UV리스트이다.
			VertexUVSet.push_back(pFbxLayer->GetUVs());
		}
		if (pFbxLayer->GetVertexColors() != nullptr)
		{
			//정점컬러 리스트이다.
			VertexColorSet.push_back(pFbxLayer->GetVertexColors());
		}
		if (pFbxLayer->GetMaterials() != nullptr)
		{
			//메터리얼 리스트이다.
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
		pObject->m_pSubIWVertexList.resize(iNumMtrl);
	}
	else
	{
		pObject->m_pSubVertexList.resize(1);
		pObject->m_pSubIWVertexList.resize(1);
	}

	int iBasePolyIndex = 0;
	// 삼각형, 사각형
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

				// 가중치
				JVertexIW iwVertex;
				if (pObject->m_bSkinned)
				{
					JWeight* weight = &pObject->m_WeightList[CornerIndex[iIndex]];
					for (int i = 0; i < 4; i++)
					{
						iwVertex.i[i] = weight->Index[i];
						iwVertex.w[i] = weight->Weight[i];
					}
				}
				else
				{
					// 일반오브젝트 에니메이션을 스키닝 케릭터 화 작업.
					iwVertex.i[0] = pObject->m_iIndex;
					iwVertex.w[0] = 1.0f;
				}

				//pObject->m_VertexList.push_back(tVertex);//36
				pObject->m_pSubVertexList[iSubMtrl].push_back(tVertex);
				pObject->m_pSubIWVertexList[iSubMtrl].push_back(iwVertex);
			}
		}

		iBasePolyIndex += iPolySize;
	}
	
}
bool JFbxImporter::CreateConstantBuffer(ID3D11Device* pDevice)
{
	HRESULT hr;
	//gpu메모리에 버퍼 할당(원하는 할당 크기)
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
