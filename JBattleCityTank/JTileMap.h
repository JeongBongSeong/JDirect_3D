#pragma once
#include "JMap.h"



class JTileMap : public JMap{
public:
	

public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
};

