#pragma once
#include"JObject2D.h"
using CollisionPlayerFunction = std::function<void(JBaseObject*, DWORD)>;
using CollisionFunction = std::function<void(JBaseObject*, DWORD)>;
using SelectFunction = std::function<void(JBaseObject*, DWORD)>;
class JObjectMgr : public JSingleton<JObjectMgr>
{
private:
	int m_iExecuteCollisionID;
	int m_iExecuteCollisionPlayerID;
	int m_iExecuteSelectID;
	std::map<int, JBaseObject*> m_PlayerObjectList;
	std::map<int, JBaseObject*> m_ObjectList;
	std::map<int, JBaseObject*> m_SelectList;

public:
	friend class JSingleton<JObjectMgr>;
public:

public:
	typedef std::map<int, CollisionPlayerFunction>::iterator FunctionIterator;
	std::map<int, CollisionPlayerFunction> m_fnCollisionPlayerExecute;
	typedef std::map<int, CollisionFunction>::iterator FunctionIterator;
	std::map<int, CollisionFunction> m_fnCollisionExecute;
	typedef std::map<int, SelectFunction>::iterator FunctionIterator;
	std::map<int, SelectFunction> m_fnSelectExecute;
public:
	void AddPlayerCollisionExecute(JBaseObject* owner, CollisionFunction func);
	void AddCollisionExecute(JBaseObject* owner, CollisionFunction func);
	void AddSelectExecute(JBaseObject* owner, CollisionFunction func);
	void DeletePlayerCollisionExecute(JBaseObject* owner);
	void DeleteCollisionExecute(JBaseObject* owner);
	void DeleteSelectExecute(JBaseObject* owner);
	bool Init();
	bool Frame();
	bool Release();
	void CallRecursive(JBaseObject* pSrcObj, DWORD dwState);
private:
	JObjectMgr();
public:
	virtual ~JObjectMgr();
};

#define I_ObjectMgr JObjectMgr::Get()