#include "JPlaneObj.h"
#include "JInput.h"
bool    JPlaneObj::SetVertexData()
{

	m_VertexList.resize(4);

	m_VertexList[0].p = JVector3(-1.0f, 1.0f, 0.0f);
	m_VertexList[0].n = JVector3(0.0f, 0.0f, -1.0f);
	m_VertexList[0].c = JVector4(1.0f, 0.0f, 0.0f, 1.0f);
	m_VertexList[0].t = JVector2(0.0f, 0.0f);
							
	m_VertexList[1].p = JVector3(1.0f, 1.0f, 0.0f);
	m_VertexList[1].n = JVector3(0.0f, 0.0f, -1.0f);
	m_VertexList[1].c = JVector4(0.0f, 1.0f, 0.0f, 1.0f);
	m_VertexList[1].t = JVector2(1.0f, 0.0f);
							
							
	m_VertexList[2].p = JVector3(-1.0f, -1.0f, 0.0f);
	m_VertexList[2].n = JVector3(0.0f, 0.0f, -1.0f);
	m_VertexList[2].c = JVector4(0.0f, 0.0f, 1.0f, 1.0f);
	m_VertexList[2].t = JVector2(0.0f, 1.0f);
							
							
	m_VertexList[3].p = JVector3(1.0f, -1.0f, 0.0f);
	m_VertexList[3].n = JVector3(0.0f, 0.0f, -1.0f);
	m_VertexList[3].c = JVector4(0.0f, 0.0f, 0.0f, 1.0f);
	m_VertexList[3].t = JVector2(1.0f, 1.0f);
	
	return true;
}
bool    JPlaneObj::SetIndexData()
{

	m_IndexList.push_back(0); m_IndexList.push_back(1); m_IndexList.push_back(2);
	m_IndexList.push_back(2); m_IndexList.push_back(1); m_IndexList.push_back(3);
	
	return true;
}
JPlaneObj::JPlaneObj()
{

}