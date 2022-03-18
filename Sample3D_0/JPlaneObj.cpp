#include "JPlaneObj.h"
#include "JInput.h"
bool    JPlaneObj::SetVertexData()
{
	// Local Coord
	// Box
	// 0		1
	//	  원점
	// 2		3
	m_VertexList.resize(4);
	// -Z plane
	//뒤
	m_VertexList[0].p = JVector3(-1.0f, 1.0f, 3.5f);
	m_VertexList[0].n = JVector3(0.0f, 0.0f, -1.0f);
	m_VertexList[0].c = JVector4(1.0f, 0.0f, 0.0f, 1.0f);
	m_VertexList[0].t = JVector2(0.0f, 0.0f);
							
	m_VertexList[1].p = JVector3(1.0f, 1.0f, 3.5f);
	m_VertexList[1].n = JVector3(0.0f, 0.0f, -1.0f);
	m_VertexList[1].c = JVector4(0.0f, 1.0f, 0.0f, 1.0f);
	m_VertexList[1].t = JVector2(1.0f, 0.0f);
							
							
	m_VertexList[2].p = JVector3(-1.0f, -1.0f, 3.5f);
	m_VertexList[2].n = JVector3(0.0f, 0.0f, -1.0f);
	m_VertexList[2].c = JVector4(0.0f, 0.0f, 1.0f, 1.0f);
	m_VertexList[2].t = JVector2(0.0f, 1.0f);
							
							
	m_VertexList[3].p = JVector3(1.0f, -1.0f, 3.5f);
	m_VertexList[3].n = JVector3(0.0f, 0.0f, -1.0f);
	m_VertexList[3].c = JVector4(0.0f, 0.0f, 0.0f, 1.0f);
	m_VertexList[3].t = JVector2(1.0f, 1.0f);
	////앞
	//m_VertexList[4].p = JVector3(1.0f, -1.0f, -0.5f);
	//m_VertexList[4].n = JVector3(0.0f, 0.0f, 1.0f);
	//m_VertexList[4].c = JVector4(0.0f, 1.0f, 1.0f, 1.0f);
	//m_VertexList[4].t = JVector2(1.0f, 1.0f);

	//m_VertexList[5].p = JVector3(1.0f, -1.0f, -0.5f);
	//m_VertexList[5].n = JVector3(0.0f, 0.0f, 1.0f);
	//m_VertexList[5].c = JVector4(1.0f, 0.0f, 1.0f, 1.0f);
	//m_VertexList[5].t = JVector2(1.0f, 1.0f);

	//m_VertexList[6].p = JVector3(1.0f, -1.0f, -0.5f);
	//m_VertexList[6].n = JVector3(0.0f, 0.0f, 1.0f);
	//m_VertexList[6].c = JVector4(1.0f, 1.0f, 0.0f, 1.0f);
	//m_VertexList[6].t = JVector2(1.0f, 1.0f);

	//m_VertexList[7].p = JVector3(1.0f, -1.0f, -0.5f);
	//m_VertexList[7].n = JVector3(0.0f, 0.0f, 1.0f);
	//m_VertexList[7].c = JVector4(1.0f, 1.0f, 1.0f, 1.0f);
	//m_VertexList[7].t = JVector2(1.0f, 1.0f);
	////
	//m_VertexList[8].p = JVector3(1.0f, -1.0f, 0.5f);
	//m_VertexList[8].n = JVector3(0.0f, 0.0f, -1.0f);
	//m_VertexList[8].c = JVector4(1.0f, 1.0f, 1.0f, 1.0f);
	//m_VertexList[8].t = JVector2(1.0f, 1.0f);

	//m_VertexList[9].p = JVector3(1.0f, -1.0f, 0.5f);
	//m_VertexList[9].n = JVector3(0.0f, 0.0f, -1.0f);
	//m_VertexList[9].c = JVector4(1.0f, 1.0f, 1.0f, 1.0f);
	//m_VertexList[9].t = JVector2(1.0f, 1.0f);

	//m_VertexList[10].p = JVector3(1.0f, -1.0f, 0.5f);
	//m_VertexList[10].n = JVector3(0.0f, 0.0f, -1.0f);
	//m_VertexList[10].c = JVector4(1.0f, 1.0f, 1.0f, 1.0f);
	//m_VertexList[10].t = JVector2(1.0f, 1.0f);

	//m_VertexList[11].p = JVector3(1.0f, -1.0f, 0.5f);
	//m_VertexList[11].n = JVector3(0.0f, 0.0f, -1.0f);
	//m_VertexList[11].c = JVector4(1.0f, 1.0f, 1.0f, 1.0f);
	//m_VertexList[11].t = JVector2(1.0f, 1.0f);
	////
	//m_VertexList[12].p = JVector3(1.0f, -1.0f, 0.5f);
	//m_VertexList[12].n = JVector3(0.0f, 0.0f, -1.0f);
	//m_VertexList[12].c = JVector4(1.0f, 1.0f, 1.0f, 1.0f);
	//m_VertexList[12].t = JVector2(1.0f, 1.0f);

	//m_VertexList[13].p = JVector3(1.0f, -1.0f, 0.5f);
	//m_VertexList[13].n = JVector3(0.0f, 0.0f, -1.0f);
	//m_VertexList[13].c = JVector4(1.0f, 1.0f, 1.0f, 1.0f);
	//m_VertexList[13].t = JVector2(1.0f, 1.0f);

	//m_VertexList[14].p = JVector3(1.0f, -1.0f, 0.5f);
	//m_VertexList[14].n = JVector3(0.0f, 0.0f, -1.0f);
	//m_VertexList[14].c = JVector4(1.0f, 1.0f, 1.0f, 1.0f);
	//m_VertexList[14].t = JVector2(1.0f, 1.0f);

	//m_VertexList[15].p = JVector3(1.0f, -1.0f, 0.5f);
	//m_VertexList[15].n = JVector3(0.0f, 0.0f, -1.0f);
	//m_VertexList[15].c = JVector4(1.0f, 1.0f, 1.0f, 1.0f);
	//m_VertexList[15].t = JVector2(1.0f, 1.0f);
	////
	return true;
}
bool    JPlaneObj::SetIndexData()
{
	//m_IndexList.clear();
	//뒤 (내가보는 방향)
	m_IndexList.push_back(0); m_IndexList.push_back(1); m_IndexList.push_back(2);
	m_IndexList.push_back(2); m_IndexList.push_back(1); m_IndexList.push_back(3);
	////앞
	//m_IndexList.push_back(5); m_IndexList.push_back(4); m_IndexList.push_back(7);
	//m_IndexList.push_back(7); m_IndexList.push_back(4); m_IndexList.push_back(5);
	////뒤
	//m_IndexList.push_back(1); m_IndexList.push_back(5); m_IndexList.push_back(3);
	//m_IndexList.push_back(3); m_IndexList.push_back(5); m_IndexList.push_back(7);
	////뒤
	//m_IndexList.push_back(4); m_IndexList.push_back(0); m_IndexList.push_back(6);
	//m_IndexList.push_back(6); m_IndexList.push_back(0); m_IndexList.push_back(2);
	return true;
}

bool JPlaneObj::Frame()
{
	/*JMatrix matRotate, matScale, matTrans;
	matRotate.ZRotate(g_fGameTimer);

	matScale.Scale(cos(g_fGameTimer) * 0.5f + 0.5f, 1.0f, 1.0f);
	matTrans.Translation(0,
		0, g_fGameTimer); */
	//m_ConstantList.matWorld = matRotate;// matScale* matRotate* matTrans;
	if (JInput::Get().GetKey(VK_LEFT))
	{
		m_vCamera.z -= g_fSecPerFrame * 1.0f;
	}
	if (JInput::Get().GetKey(VK_RIGHT))
	{
		m_vCamera.z += g_fSecPerFrame * 1.0f;
	}
	if (JInput::Get().GetKey(VK_UP))
	{
		m_vCamera.y += g_fSecPerFrame * 1.0f;
	}
	if (JInput::Get().GetKey(VK_DOWN))
	{
		m_vCamera.y -= g_fSecPerFrame * 1.0f;
	}
	JVector3 vTarget(0, 0, 0);
	JVector3 vUp(0, 1, 0);
	m_matView.CreateViewLook(m_vCamera, vTarget, vUp);
	// Projection
	m_matProj.PerspectiveFovLH(1.0f, 100.0f, JBASIS_PI * 0.5f, g_rtClient.right / g_rtClient.bottom);

	m_ConstantList.matWorld = m_matWorld.Transpose();
	m_ConstantList.matView = m_matView.Transpose();
	m_ConstantList.matProj = m_matProj.Transpose();
	JObject3D::Frame();
	//m_ConstantList.matWorld=m_ConstantList.matWorld.Transpose();
	return true;
}
