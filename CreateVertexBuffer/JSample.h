#pragma once
#pragma comment(lib,"JCoreLib.lib")
#include "JDxObject.h"
#include"JCore.h"

class JSample : public JCore
{	
public:
	vector<JDxObject> m_ObjectList;
public:
	JSample();
	~JSample();
public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
};

