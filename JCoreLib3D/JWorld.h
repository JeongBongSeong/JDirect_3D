#pragma once
#include"JObject2D.h"
class JWorld
{
public:
	enum JWorldID { J_LOADING, J_LOGIN, J_LOBBY, J_ZONE, J_RESULT, };
	ID3D11Device* m_pd3dDevice;
	ID3D11DeviceContext* m_pContext;
	bool m_bLoadZone = false;
public:
	static JWorld* m_pWorld;
	std::vector<std::shared_ptr<JObject2D>> m_UIObj;
	std::vector<std::shared_ptr<JObject2D>> m_ItemObj;
	std::vector<std::shared_ptr<JObject2D>> m_NpcObj;
	std::vector<std::shared_ptr<JObject2D>> m_MapObj;
	using m_mapIter = std::vector<std::shared_ptr<JObject2D>>::iterator;
public:
	virtual bool Load(std::wstring saveFile);
	virtual bool Init() = 0;
	virtual bool Frame() = 0;
	virtual bool Render() = 0;
	virtual bool Release();
public:
	JWorld();
	virtual ~JWorld();
};

