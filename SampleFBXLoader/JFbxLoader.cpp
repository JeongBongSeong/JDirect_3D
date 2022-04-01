#include "JFbxLoader.h"

bool JFbxLoader::PreProcess(FbxNode* node)
{
	//FbxMesh* pMesh = node->GetMesh();
	//if (pMesh)
	//{
	//	JFbxObj*
	//}
	//int iNumChild = node->GetChildCount();
	//for (int iNode = 0; iNode < iNumChild; iNode++)
	//{
	//	FbxNode* pChildNode = node->GetChild(iNode);
	//	PreProcess(pChildNode);
	//}
	return true;
}

bool JFbxLoader::Load(std::string filename)
{
	bool bRet = m_pFbxImporter->Initialize(filename.c_str());
	bRet = m_pFbxImporter->Import(m_pFbxScene);

	return true;
}



bool JFbxLoader::Init()
{
	m_pFbxManager = FbxManager::Create();
	m_pFbxImporter = FbxImporter::Create(m_pFbxManager,"");
	m_pFbxScene = FbxScene::Create(m_pFbxManager, "");

	return true;
}

bool JFbxLoader::Frame()
{
	return true;
}

bool JFbxLoader::Render()
{
	return true;
}

bool JFbxLoader::Release()
{
	m_pFbxManager->Destroy();
	m_pFbxImporter->Destroy();
	//m_pFbxScene->Destroy();
	return true;
}
