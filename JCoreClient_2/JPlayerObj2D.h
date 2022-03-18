#pragma once
#include "JObject2D.h"
class JPlayerObj2D : public JObject2D
{
public:
	bool	Frame() override;
	JPlayerObj2D();
	virtual ~JPlayerObj2D();
};
