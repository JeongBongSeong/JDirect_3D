#pragma once
#include "JWorld.h"
class JLoginWorld : public JWorld
{


public:
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();
};

