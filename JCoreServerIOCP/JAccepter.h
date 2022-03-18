#pragma once
#include"JThread.h"
class JAccepter : public JThread
{
public:
	JAccepter();
	JAccepter(LPVOID value);

public:
	bool Run() override;

};

