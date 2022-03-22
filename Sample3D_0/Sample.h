#pragma once
#include "JCore.h"
#include "JPlaneObj.h"
#include "JCamera.h"
#include "JMap.h"
#include "JSkyObj.h"
#include "JBoxObj.h"

class Sample : public JCore
{
	JCamera		    m_Camera;
	JMap	       m_MapObj;
	JBoxObj m_PlayerObj;
	JPlaneObj       m_ObjB;

	JSkyObj       m_SkyObj;
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

