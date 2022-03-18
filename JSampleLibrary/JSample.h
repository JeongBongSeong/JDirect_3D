#pragma once
#pragma comment(lib,"JCoreLib.lib")
#include"JCore.h"
#include"d3d11.h"
class JSample : public JCore
{	
	
public:
	JSample();
	~JSample();
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};

