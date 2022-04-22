#define  _CRT_SECURE_NO_WARNINGS
#include "JFbxObj.h"
bool	JFbx::Init()
{
	m_fTime = 61;
	return true;
}
bool	JFbx::Frame()
{
	/*m_fTime += g_fSecPerFrame * m_pMeshImp->m_Scene.iFrameSpeed * m_fDir * m_fSpeed;
	if (m_fTime >= m_pMeshImp->m_Scene.iEnd)
	{
		m_fDir *= -1.0f;
	}
	if (m_fTime <= m_pMeshImp->m_Scene.iStart)
	{
		m_fDir *= -1.0f;
	}
	int iFrame = m_fTime;
	iFrame = max(0, min(m_pMeshImp->m_Scene.iEnd, iFrame));*/
	/*for (int iObj = 0; iObj < m_pMeshImp->m_TreeList.size(); iObj++)
	{
		JFbxModel* pObject = m_pMeshImp->m_TreeList[iObj];
		if (pObject->m_AnimTrack.size() > 0)
		{
			auto binepose = pObject->m_matBindPoseMap.find(pObject->m_iIndex);
			if (binepose != pObject->m_matBindPoseMap.end())
			{
				T::TMatrix matInverseBindpose = binepose->second;
				m_matBoneArray.matBoneWorld[iObj] =
					matInverseBindpose *
					pObject->m_AnimTrack[iFrame].matTrack;
			}
			else
			{
				m_matBoneArray.matBoneWorld[iObj] =
					pObject->m_AnimTrack[iFrame].matTrack;
			}
		}
		T::D3DXMatrixTranspose(&m_matBoneArray.matBoneWorld[iObj],&m_matBoneArray.matBoneWorld[iObj]);
	}	*/
	return true;
}
T::TMatrix JFbx::Interplate(JFbxImporter* pAnimImp, JFbxModel* pModel, float fTime)
{
	T::TMatrix matAnim;
	JScene tScene = pAnimImp->m_Scene;
	int iStart = max(tScene.iStart, fTime);
	int iEnd = min(tScene.iEnd, fTime + 1);

	JTrack A = pModel->m_AnimTrack[iStart];
	JTrack B = pModel->m_AnimTrack[iEnd];
	float s = fTime - (float)iStart; // 0~1
	T::TVector3 pos;
	T::D3DXVec3Lerp(&pos, &A.t, &B.t, s);
	T::TVector3 scale;
	T::D3DXVec3Lerp(&scale, &A.s, &B.s, s);
	T::TQuaternion rotation;
	T::D3DXQuaternionSlerp(&rotation, &A.r, &B.r, s);
	T::TMatrix matScale;
	T::D3DXMatrixScaling(&matScale, scale.x, scale.y, scale.z);
	T::TMatrix matRotation;
	T::D3DXMatrixRotationQuaternion(&matRotation, &rotation);

	matAnim = matScale * matRotation;
	matAnim._41 = pos.x;
	matAnim._42 = pos.y;
	matAnim._43 = pos.z;
	//T::TMatrix matTrans;
	//T::D3DXMatrixTranslation(&matTrans, pos.x, pos.y, pos.z);
	//matAnim = pModel->m_AnimTrack[(int)fTime].matTrack;
	return matAnim;
}
bool	JFbx::Render()
{
	JFbxImporter* pAnimImp = nullptr;
	if (m_pAnimImporter != nullptr)
	{
		pAnimImp = m_pAnimImporter;
	}
	else
	{
		pAnimImp = m_pMeshImp;
	}
	m_fTime += g_fSecPerFrame * pAnimImp->m_Scene.iFrameSpeed * m_fDir * 0.33f;//m_fSpeed;
	if (m_fTime >= pAnimImp->m_Scene.iEnd)
	{
		//m_fDir *= -1.0f;
		m_fTime = pAnimImp->m_Scene.iStart;
	}
	int iFrame = m_fTime;
	iFrame = max(0, min(pAnimImp->m_Scene.iEnd-1, iFrame));

	for (int iObj = 0; iObj < m_pMeshImp->m_DrawList.size(); iObj++)
	{
		JFbxModel* pFbxObj = m_pMeshImp->m_DrawList[iObj];

		if (pFbxObj->m_bSkinned)
		{
			for (auto data : pAnimImp->m_pFbxModelMap)
			{
				std::wstring name = data.first;
				JFbxModel* pAnimModel = data.second;
				auto model = m_pMeshImp->m_pFbxModelMap.find(name);
				if (model == m_pMeshImp->m_pFbxModelMap.end())
				{
					continue; // error
				}
				JFbxModel* pTreeModel = model->second;
				if (pTreeModel == nullptr)
				{
					continue; // error
				}
				auto binepose = pFbxObj->m_dxMatrixBindPoseMap.find(name);
				if (binepose != pFbxObj->m_dxMatrixBindPoseMap.end() && pAnimModel)
				{
					TMatrix matInverseBindpose = binepose->second;
					m_matBoneArray.matBoneWorld[pTreeModel->m_iIndex] =
						matInverseBindpose *
						Interplate(pAnimImp, pAnimModel, m_fTime);
					//pAnimModel->m_AnimTrack[iFrame].matTrack;
				}
				T::D3DXMatrixTranspose(&m_matBoneArray.matBoneWorld[pTreeModel->m_iIndex],
					&m_matBoneArray.matBoneWorld[pTreeModel->m_iIndex]);

			}
		}
		else
		{
			for (int inode = 0; inode < m_pMeshImp->m_TreeList.size(); inode++)
			{
				JFbxModel* pFbxModel = m_pMeshImp->m_TreeList[inode];
				if (pFbxModel->m_AnimTrack.size() > 0)
				{
					m_matBoneArray.matBoneWorld[inode] =
						Interplate(pAnimImp, pFbxModel, m_fTime);
					//pFbxModel->m_AnimTrack[iFrame].matTrack;

				}
				T::D3DXMatrixTranspose(&m_matBoneArray.matBoneWorld[inode],
					&m_matBoneArray.matBoneWorld[inode]);
			}
		}

		m_pContext->UpdateSubresource(m_pMeshImp->m_pBoneCB, 0, NULL, &m_matBoneArray, 0, 0);
		m_pContext->VSSetConstantBuffers(2, 1, &m_pMeshImp->m_pBoneCB);

		T::TVector3 vLight(cosf(g_fGameTimer) * 100.0f, 100, sinf(g_fGameTimer) * 100.0f);
		T::D3DXVec3Normalize(&vLight, &vLight);
		vLight = vLight * -1.0f;
		pFbxObj->m_LightConstantList.vLightDir.x = vLight.x;
		pFbxObj->m_LightConstantList.vLightDir.y = vLight.y;
		pFbxObj->m_LightConstantList.vLightDir.z = vLight.z;
		pFbxObj->m_LightConstantList.vLightDir.w = 1.0f;

		pFbxObj->SetMatrix(&m_matWorld, &m_matView, &m_matProj);
		pFbxObj->Render();
	}
	return true;
}
bool	JFbx::Release()
{
	return true;
}