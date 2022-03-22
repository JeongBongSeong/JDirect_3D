#include "JSkyObj.h"
bool JSkyObj::LoadTexture(const TCHAR* szColorFileName,
	const TCHAR* szMaskFileName)
{

	m_pTexArray[0] = I_Texture.Load(L"..\\..\\data\\sky\\st00_cm_front.bmp");
	m_pTexArray[1] = I_Texture.Load(L"..\\..\\data\\sky\\st00_cm_back.bmp");
	m_pTexArray[2] = I_Texture.Load(L"..\\..\\data\\sky\\st00_cm_right.bmp");
	m_pTexArray[3] = I_Texture.Load(L"..\\..\\data\\sky\\st00_cm_left.bmp");
	m_pTexArray[4] = I_Texture.Load(L"..\\..\\data\\sky\\st00_cm_up.bmp");
	m_pTexArray[5] = I_Texture.Load(L"..\\..\\data\\sky\\st00_cm_down.bmp");

	m_TextureDesc = m_pTexArray[0]->m_TextureDesc;
	return true;
}

bool		JSkyObj::SetVertexData()
{

	int index = 0;
	m_VertexList.resize(24);
	m_VertexList[0] = JVertex(JVector3(-1.0f, 1.0f, -1.0f), JVector3(0.0f, 0.0f, -1.0f), JVector4(1.0f, 0.0f, 0.0f, 1.0f), JVector2(0.0f, 0.0f));
	m_VertexList[1] = JVertex(JVector3(1.0f, 1.0f, -1.0f), JVector3(0.0f, 0.0f, -1.0f), JVector4(1.0f, 0.0f, 0.0f, 1.0f), JVector2(1.0f, 0.0f));
	m_VertexList[2] = JVertex(JVector3(1.0f, -1.0f, -1.0f), JVector3(0.0f, 0.0f, -1.0f), JVector4(1.0f, 0.0f, 0.0f, 1.0f), JVector2(1.0f, 1.0f));
	m_VertexList[3] = JVertex(JVector3(-1.0f, -1.0f, -1.0f), JVector3(0.0f, 0.0f, -1.0f), JVector4(1.0f, 0.0f, 0.0f, 1.0f), JVector2(0.0f, 1.0f));
	// µÞ¸é
	m_VertexList[4] = JVertex(JVector3(1.0f, 1.0f, 1.0f), JVector3(0.0f, 0.0f, 1.0f), JVector4(0.0f, 0.0f, 0.0f, 1.0f), JVector2(0.0f, 0.0f));
	m_VertexList[5] = JVertex(JVector3(-1.0f, 1.0f, 1.0f), JVector3(0.0f, 0.0f, 1.0f), JVector4(0.0f, 1.0f, 0.0f, 1.0f), JVector2(1.0f, 0.0f));
	m_VertexList[6] = JVertex(JVector3(-1.0f, -1.0f, 1.0f), JVector3(0.0f, 0.0f, 1.0f), JVector4(0.0f, 1.0f, 0.0f, 1.0f), JVector2(1.0f, 1.0f));
	m_VertexList[7] = JVertex(JVector3(1.0f, -1.0f, 1.0f), JVector3(0.0f, 0.0f, 1.0f), JVector4(0.0f, 1.0f, 0.0f, 1.0f), JVector2(0.0f, 1.0f));

	// ¿À¸¥ÂÊ
	m_VertexList[8] = JVertex(JVector3(1.0f, 1.0f, -1.0f), JVector3(1.0f, 0.0f, 0.0f), JVector4(0.0f, 0.0f, 1.0f, 1.0f), JVector2(0.0f, 0.0f));
	m_VertexList[9] = JVertex(JVector3(1.0f, 1.0f, 1.0f), JVector3(1.0f, 0.0f, 0.0f), JVector4(0.0f, 0.0f, 1.0f, 1.0f), JVector2(1.0f, 0.0f));
	m_VertexList[10] = JVertex(JVector3(1.0f, -1.0f, 1.0f), JVector3(1.0f, 0.0f, 0.0f), JVector4(0.0f, 0.0f, 1.0f, 1.0f), JVector2(1.0f, 1.0f));
	m_VertexList[11] = JVertex(JVector3(1.0f, -1.0f, -1.0f), JVector3(1.0f, 0.0f, 0.0f), JVector4(0.0f, 0.0f, 1.0f, 1.0f), JVector2(0.0f, 1.0f));

	// ¿ÞÂÊ
	m_VertexList[12] = JVertex(JVector3(-1.0f, 1.0f, 1.0f), JVector3(-1.0f, 0.0f, 0.0f), JVector4(1.0f, 1.0f, 0.0f, 1.0f), JVector2(0.0f, 0.0f));
	m_VertexList[13] = JVertex(JVector3(-1.0f, 1.0f, -1.0f), JVector3(-1.0f, 0.0f, 0.0f), JVector4(1.0f, 1.0f, 0.0f, 1.0f), JVector2(1.0f, 0.0f));
	m_VertexList[14] = JVertex(JVector3(-1.0f, -1.0f, -1.0f), JVector3(-1.0f, 0.0f, 0.0f), JVector4(1.0f, 1.0f, 0.0f, 1.0f), JVector2(1.0f, 1.0f));
	m_VertexList[15] = JVertex(JVector3(-1.0f, -1.0f, 1.0f), JVector3(-1.0f, 0.0f, 0.0f), JVector4(1.0f, 1.0f, 0.0f, 1.0f), JVector2(0.0f, 1.0f));

	// À­¸é
	m_VertexList[16] = JVertex(JVector3(-1.0f, 1.0f, 1.0f), JVector3(0.0f, 1.0f, 0.0f), JVector4(1.0f, 0.5f, 1.0f, 1.0f), JVector2(0.0f, 0.0f));
	m_VertexList[17] = JVertex(JVector3(1.0f, 1.0f, 1.0f), JVector3(0.0f, 1.0f, 0.0f), JVector4(1.0f, 0.5f, 1.0f, 1.0f), JVector2(1.0f, 0.0f));
	m_VertexList[18] = JVertex(JVector3(1.0f, 1.0f, -1.0f), JVector3(0.0f, 1.0f, 0.0f), JVector4(1.0f, 0.5f, 1.0f, 1.0f), JVector2(1.0f, 1.0f));
	m_VertexList[19] = JVertex(JVector3(-1.0f, 1.0f, -1.0f), JVector3(0.0f, 1.0f, 0.0f), JVector4(1.0f, 0.5f, 1.0f, 1.0f), JVector2(0.0f, 1.0f));

	// ¾Æ·§¸é
	m_VertexList[20] = JVertex(JVector3(-1.0f, -1.0f, -1.0f), JVector3(0.0f, -1.0f, 0.0f), JVector4(0.0f, 1.0f, 1.0f, 1.0f), JVector2(0.0f, 0.0f));
	m_VertexList[21] = JVertex(JVector3(1.0f, -1.0f, -1.0f), JVector3(0.0f, -1.0f, 0.0f), JVector4(0.0f, 1.0f, 1.0f, 1.0f), JVector2(1.0f, 0.0f));
	m_VertexList[22] = JVertex(JVector3(1.0f, -1.0f, 1.0f), JVector3(0.0f, -1.0f, 0.0f), JVector4(0.0f, 1.0f, 1.0f, 1.0f), JVector2(1.0f, 1.0f));
	m_VertexList[23] = JVertex(JVector3(-1.0f, -1.0f, 1.0f), JVector3(0.0f, -1.0f, 0.0f), JVector4(0.0f, 1.0f, 1.0f, 1.0f), JVector2(0.0f, 1.0f));
	return true;
}
bool		JSkyObj::SetIndexData()
{
	m_IndexList.resize(36);
	int iIndex = 0;
	m_IndexList[iIndex++] = 0; 	m_IndexList[iIndex++] = 1; 	m_IndexList[iIndex++] = 2; 	m_IndexList[iIndex++] = 0;	m_IndexList[iIndex++] = 2; 	m_IndexList[iIndex++] = 3;
	m_IndexList[iIndex++] = 4; 	m_IndexList[iIndex++] = 5; 	m_IndexList[iIndex++] = 6; 	m_IndexList[iIndex++] = 4;	m_IndexList[iIndex++] = 6; 	m_IndexList[iIndex++] = 7;
	m_IndexList[iIndex++] = 8; 	m_IndexList[iIndex++] = 9; 	m_IndexList[iIndex++] = 10; m_IndexList[iIndex++] = 8;	m_IndexList[iIndex++] = 10; m_IndexList[iIndex++] = 11;
	m_IndexList[iIndex++] = 12; m_IndexList[iIndex++] = 13; m_IndexList[iIndex++] = 14; m_IndexList[iIndex++] = 12;	m_IndexList[iIndex++] = 14; m_IndexList[iIndex++] = 15;
	m_IndexList[iIndex++] = 16; m_IndexList[iIndex++] = 17; m_IndexList[iIndex++] = 18; m_IndexList[iIndex++] = 16;	m_IndexList[iIndex++] = 18; m_IndexList[iIndex++] = 19;
	m_IndexList[iIndex++] = 20; m_IndexList[iIndex++] = 21; m_IndexList[iIndex++] = 22; m_IndexList[iIndex++] = 20;	m_IndexList[iIndex++] = 22; m_IndexList[iIndex++] = 23;
	return true;
}
bool	JSkyObj::PostRender()
{
	for (int iTex = 0; iTex < 6; iTex++)
	{
		m_pContext->PSSetShaderResources(0, 1,
			m_pTexArray[iTex]->m_pSRV.GetAddressOf());
		m_pContext->DrawIndexed(6, 6 * iTex, 0);
	}
	return true;
}
JSkyObj::JSkyObj()
{

}
JSkyObj::~JSkyObj()
{

}