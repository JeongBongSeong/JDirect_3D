#pragma once
#pragma comment(lib,"JCoreLib.lib")
#include"JStd.h"

struct SimpleVertex
{
	JVector2 v;
};
class JDxObject
{
	float   m_fSpeed;
	JVector2 m_vPos;
	std::vector<SimpleVertex> m_InitScreenList;
	std::vector<SimpleVertex> m_VertexList;
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11InputLayout* m_pVertexLayout;
	ID3D11VertexShader* m_pVertexShader;
	ID3D11PixelShader* m_pPixelShader;

	ID3D11Device* m_pd3dDevice;
	ID3D11DeviceContext* m_pContext;


	ID3DBlob* m_pVSBlob = nullptr;
	ID3DBlob* m_pPSBlob = nullptr;
public:
	void    SetDevice(ID3D11Device* m_pd3dDevice, ID3D11DeviceContext* m_pContext);
	bool	Create(ID3D11Device* m_pd3dDevice, ID3D11DeviceContext* m_pContext, JVector2 pos, float fWidth, float fHeight);
	// 화면좌표 위치를 중점으로 NDC 변환
	void	Convert( JVector2 center, float fWidth, float fHeight, std::vector<SimpleVertex>& retList);
	// 화면좌표계를 NDC 변환
	void	Convert(std::vector<SimpleVertex>& list, std::vector<SimpleVertex>& retList);
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();
public:
	JDxObject();
	~JDxObject();
};