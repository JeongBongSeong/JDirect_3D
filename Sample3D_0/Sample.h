#pragma once
#include"JCore.h"
#include"JBoxObj.h"
#include"JPlaneObj.h"


class Sample : public JCore
{
	JPlaneObj m_Obj;
public:
	virtual void	CreateResizeDevice(UINT iWidth, UINT iHeight) override;
	virtual void	DeleteResizeDevice(UINT iWidth, UINT iHeight) override;
public:
	virtual bool	Init()  override;
	virtual bool	Frame()  override;
	virtual bool	Render()  override;
	virtual bool	Release()  override;
public:
	Sample();
	virtual ~Sample();
};

