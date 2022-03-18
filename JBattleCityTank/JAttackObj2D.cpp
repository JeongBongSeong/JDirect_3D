#include "JAttackObj2D.h"



void JAttackObj2D::HitOverlap(JBaseObject* pObj, DWORD dwState)
{
    if (dwState == JCollisionType::Overlap)
    {
        pObj->m_bCheck = true;
        pObj->m_bDead = true;
        m_bDead=true;
        //
        
        //Ÿ����ũ��ġ ���� ����Ʈ 
        //pObj->m_vPos
    }
}

void JAttackObj2D::SetEffect()
{
}


void JAttackObj2D::SettingPosition(JVector2* pos,JVector2 *dir)
{
    m_vPos = *pos;
    m_vDirection = *dir;
}
bool JAttackObj2D::Frame()
{
    if (m_bDead == true) return false;
    JVector2 p;
    if (m_vPos.y < m_rtIngame.top)      //����
    {
        m_bDead = true;
        return true;
    }
    if (m_vPos.x > m_rtIngame.right)    //������
    {
        m_bDead = true;
        return true;
    }
    if (m_vPos.x < m_rtIngame.left)     //����
    {
        m_bDead = true;
        return true;
    }  
    if (m_vPos.y > m_rtIngame.bottom)   //�Ʒ���
    {
        m_bDead = true;
        return true;
    }

    if (m_vDirection == JVector2(0,-1)) //��
    {
        SetRectSource({ 323, 102, 3, 4 });
    }
    if (m_vDirection == JVector2(0, 1)) //�Ʒ�
    {
        SetRectSource({ 339, 102, 3, 4 });
    }
    if (m_vDirection == JVector2(-1, 0)) // ����
    {
        SetRectSource({ 330, 102, 4, 3 });
    }
    if (m_vDirection == JVector2(1, 0)) // ������
    {
        SetRectSource({ 346, 102, 4, 3 });
    }

    p = m_vDirection * (m_fSpeed * g_fSecPerFrame);
    AddPosition(p);
    return true;
}

JAttackObj2D::JAttackObj2D()
{
    m_vDirection = JVector2(0, -1);
    m_fSpeed = 300.0f; //50.0f;
    m_dwCollisionType = JCollisionType::Overlap;
    m_dwSelectType = JSelectType::Select_Overlap;
}

JAttackObj2D::~JAttackObj2D()
{
}