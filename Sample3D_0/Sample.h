#pragma once
#include "JCore.h"
#include "JPlaneObj.h"
#include "JCamera.h"
#include "JMap.h"

class Sample : public JCore
{
	JCamera		    m_Camera;
	JMap	       m_MapObj;
	JPlaneObj       m_PlayerObj;
	JPlaneObj       m_ObjB;
public:
	virtual void	CreateResizeDevice(UINT iWidth, UINT iHeight) override;
	virtual void	DeleteResizeDevice(UINT iWidth, UINT iHeight) override;
	virtual bool	Init()  override;
	virtual bool	Frame()  override;
	virtual bool	Render()  override;
	virtual bool	Release()  override;	
public:
	Sample();
	virtual ~Sample();
};

