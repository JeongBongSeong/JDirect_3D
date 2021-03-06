#pragma once
#include "JFbxImporter.h"

class JFbx : public JObject3D
{
public:
	JFbxImporter* m_pMeshImp = nullptr;
	JFbxImporter* m_pAnimImporter;

	float m_fDir = 1.0f;
	float m_fTime = 0.0f;
	float m_fSpeed = 1.0f;
	JBoneWorld	  m_matBoneArray;
	std::vector<JFbx>	m_DrawList;
public:
	virtual bool	Init() override;
	virtual bool	Frame() override;
	virtual bool	Render() override;
	virtual bool    Release() override;

public:
	T::TMatrix Interplate(JFbxImporter* pAnimImp, JFbxModel* pModel, float fTime);
};