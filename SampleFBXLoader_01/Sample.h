#pragma once
#include "JCore.h"
//#include "JPlaneObj.h"
//#include "JCamera.h"
//#include "JMap.h"
#include "JSkyObj.h"
//#include "JBoxObj.h"
//#include "JQuadtree.h" 
#include "JFbxObj.h"
#define  MAX_NUM_OBJECTS 100

class Sample : public JCore
{
public:
	std::vector<JFbxImporter> m_FbxObj;
	JSkyObj m_SkyObj;
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

