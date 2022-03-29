#pragma once
#include <iostream>
#include <queue>
#include <stack>
#include <vector> // �迭(���Ҵ� ������)
#include <list>
#include "JObject3D.h"
using namespace std;
struct JMapObject
{
	std::wstring  name;
	T::TMatrix matWorld;
	T::TVector3 vPos;
	JBox       box;
	JObject3D* pObject;
	T::TVector3 m_vRight;
	T::TVector3 m_vUp;
	T::TVector3 m_vLook;
	void		UpdateData()
	{
		m_vRight.x = matWorld._11;
		m_vRight.y = matWorld._12;
		m_vRight.z = matWorld._13;
		m_vUp.x = matWorld._21;
		m_vUp.y = matWorld._22;
		m_vUp.z = matWorld._23;
		m_vLook.x = matWorld._31;
		m_vLook.y = matWorld._32;
		m_vLook.z = matWorld._33;

		T::D3DXVec3Normalize(&m_vRight, &m_vRight);
		T::D3DXVec3Normalize(&m_vUp, &m_vUp);
		T::D3DXVec3Normalize(&m_vLook, &m_vLook);
	}
	void		UpdateCollision()
	{
		box.vAxis[0] = m_vRight;
		box.vAxis[1] = m_vUp;
		box.vAxis[2] = m_vLook;

		// GenAABB();
		box.vMin = T::TVector3(100000, 100000, 100000);
		box.vMax = T::TVector3(-100000, -100000, -100000);
		for (int iV = 0; iV < 8; iV++)
		{
			T::TVector3 pos;
			T::D3DXVec3TransformCoord(&pos, &box.vList[iV], &matWorld);
			if (box.vMin.x > pos.x)
			{
				box.vMin.x = pos.x;
			}
			if (box.vMin.y > pos.y)
			{
				box.vMin.y = pos.y;
			}
			if (box.vMin.z > pos.z)
			{
				box.vMin.z = pos.z;
			}

			if (box.vMax.x < pos.x)
			{
				box.vMax.x = pos.x;
			}
			if (box.vMax.y < pos.y)
			{
				box.vMax.y = pos.y;
			}
			if (box.vMax.z < pos.z)
			{
				box.vMax.z = pos.z;
			}
		}

		T:TVector3 vHalf = box.vMax - box.vMiddle;
		box.size.x = fabs(T::D3DXVec3Dot(&box.vAxis[0], &vHalf));
		box.size.y = fabs(T::D3DXVec3Dot(&box.vAxis[1], &vHalf));
		box.size.z = fabs(T::D3DXVec3Dot(&box.vAxis[2], &vHalf));
		box.vMiddle = (box.vMin + box.vMax);
		box.vMiddle /= 2.0f;
	}
};
class JNode
{
public:
	int m_iIndex = 0; //��� ���� ���� ��ȣ
	JNode* m_pParent = nullptr; //�ش� ����� �θ��� (��Ʈ�� ��� nullptr)
	JBox m_Box;		//
	int m_iDepth = 0;	// ���� ��ġ�� level�� �� (����)	0 == rootNode
	bool b_Leaf = false;	//�� ��尡 leafNode���� Ȯ��
	std::vector<JNode*> m_pChild;	//�ڽĳ�� (����Ʈ���� ���ɰ�� 4�� ��Ʈ���� ��� 8��)
	std::vector<int> CornerList;	//�����ε����� ����Ʈ
};

