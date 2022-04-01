#pragma once

#include "JObject3D.h"
#include <fbxsdk.h>
class JFbxLoader : public JObject3D
{
public:
	FbxManager* m_pFbxManager;
	FbxImporter* m_pFbxImporter;
	FbxScene* m_pFbxScene;
	FbxNode* m_pRootNode;
public:
	virtual bool Load(std::string filename);
	virtual bool PreProcess(FbxNode* node);
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
};

