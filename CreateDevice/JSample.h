#pragma once
#include"JCore.h"
class JSample : public JCore
{
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};

