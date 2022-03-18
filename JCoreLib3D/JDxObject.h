#pragma once
#include"JTextureMgr.h"
#include"JShaderMgr.h"
#include "JDxState.h"

struct SimpleVertex
{
	JVector2 v;
	JVector2 t;
};
enum JCollisionType
{
	Block = 0,
	Overlap,
	Ignore,
}; 

enum JSelectType
{
	Select_Block = 0,
	Select_Overlap,
	Select_Ignore,
};
// 0001  - �⺻
// 0010  - ����
// 0100  - ����
// 1000  - ����ź
// 0111 = 7(�Ӽ�)
// 1111 = 15
enum JSelectState
{
	J_DEFAULT = 0,  // Ŀ���� ���� ���� ��(J_FOCUS���¿��� �ٸ� ���� J_ACTIVE�ϸ� ��ȯ�ȴ�.)
	J_HOVER = 1,	// Ŀ���� ���� ���� ��
	J_FOCUS = 2,	// J_ACTIVE���¿��� ���� ��ư�� �ٸ� ������ ������ ��(���)
	J_ACTIVE = 4,	// ���콺 ���� ��ư ������ ���� ��
	J_SELECTED = 8, // J_ACTIVE ���¿��� ���ɹ�ư ������ ��
};

class JBaseObject
{
public:
	std::wstring m_csName;
public:
	JBaseObject* m_pParent = nullptr;
	bool m_bDead;
	bool m_bCheck;
	int m_iCollisionPlayerID;
	int m_iCollisionID;
	int m_iSelectID;
	float m_fSpeed;
	float m_fCurrentSpeed;
	float m_fWidth;
	float m_fHeight;
	JRect m_rtCollision;
	DWORD m_dwCollisionType;
	DWORD m_dwSelectType;
	DWORD m_dwSelectState;
	DWORD m_dwPreSelectState;
	bool m_bSelect;
	bool m_bAlphaBlend;

public:
	virtual void HitOverlap(JBaseObject* pObj, DWORD dwState);
	virtual void HitSelect(JBaseObject* pObj, DWORD dwState);
	virtual void SetCollisionType(DWORD dwCollisionType, DWORD dwSelectType)
	{
		m_dwCollisionType = dwCollisionType;
		m_dwSelectType = dwSelectType;
	}
public:
	JBaseObject()
	{
		m_bCheck = false;
		m_bDead = false;
		m_bSelect = false;
		m_bAlphaBlend = true;
		m_dwSelectState = J_DEFAULT;
		m_iCollisionPlayerID = -1;
		m_iCollisionID = -1;
		m_iSelectID = -1;
		m_dwCollisionType = JCollisionType::Ignore;
		m_dwSelectType = JSelectType::Select_Ignore;
		m_fCurrentSpeed = 0;
	}

};

struct JIndex
{
	DWORD _0;
	DWORD _1;
	DWORD _2;
};

struct JConstantData
{
	JVector4 Color;
	JVector4 Timer;
};

class JDxObject : public JBaseObject
{
public:
	JTexture* m_pColorTex = nullptr;
	JTexture* m_pMaskTex = nullptr;
	JShader* m_pVShader = nullptr;
	JShader* m_pPShader = nullptr;
public:
	D3D11_TEXTURE2D_DESC m_TextureDesc;
	

public:
	std::vector<SimpleVertex> m_InitScreenList;
	std::vector<SimpleVertex> m_VertexList;
	ID3D11Buffer* m_pVertexBuffer = nullptr;

	std::vector<DWORD> m_IndexList;
	ID3D11Buffer* m_pIndexBuffer = nullptr;

	JConstantData    m_ConstantList;
	ID3D11Buffer* m_pConstantBuffer = nullptr;

	ID3D11InputLayout* m_pVertexLayout = nullptr;

	ID3D11Device* m_pd3dDevice;
	ID3D11DeviceContext* m_pContext = nullptr;

public:
	void    SetDevice(ID3D11Device* m_pd3dDevice, ID3D11DeviceContext* m_pContext);
	virtual bool LoadTexture(const TCHAR* szColorFileName, const TCHAR* szMaskFileName);
	virtual bool    SetVertexData();
	virtual bool	SetIndexData();
	virtual bool	SetConstantData();
	virtual bool	Create(ID3D11Device* m_pd3dDevice, ID3D11DeviceContext* m_pContext, const TCHAR* szShaderFileName = nullptr, const TCHAR* szColorFileName = nullptr, const TCHAR* szMaskFileName = nullptr);
public:
	virtual bool	CreateVertexBuffer();
	virtual bool    CreateIndexBuffer();
	virtual bool	CreateConstantBuffer();
	virtual bool    CreateVertexShader(const TCHAR* szFile);
	virtual bool    CreatePixelShader(const TCHAR* szFile);
	virtual bool    CreateInputLayout();
public:
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();
public:
	JDxObject();
	~JDxObject();
};