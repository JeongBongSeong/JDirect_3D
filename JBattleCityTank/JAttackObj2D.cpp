#include "JAttackObj2D.h"



void JAttackObj2D::HitOverlap(JBaseObject* pObj, DWORD dwState)
{
    if (dwState == JCollisionType::Overlap)
    {
        pObj->m_bCheck = true;
        pObj->m_bDead = true;
        m_bDead=true;
        //
        
        //Å¸°ÙÅÊÅ©À§Ä¡ Æø¹ß ÀÌÆåÆ® 
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
    if (m_vPos.y < m_rtIngame.top)      //À§·Î
    {
        m_bDead = true;
        return true;
    }
    if (m_vPos.x > m_rtIngame.right)    //¿À¸¥ÂÊ
    {
        m_bDead = true;
        return true;
    }
    if (m_vPos.x < m_rtIngame.left)     //¿ÞÂÊ
    {
        m_bDead = true;
        return true;
    }  
    if (m_vPos.y > m_rtIngame.bottom)   //¾Æ·¡·Î
    {
        m_bDead = true;
        return true;
    }

    if (m_vDirection == JVector2(0,-1)) //À§
    {
        SetRectSource({ 323, 102, 3, 4 });
    }
    if (m_vDirection == JVector2(0, 1)) //¾Æ·¡
    {
        SetRectSource({ 339, 102, 3, 4 });
    }
    if (m_vDirection == JVector2(-1, 0)) // ¿ÞÂÊ
    {
        SetRectSource({ 330, 102, 4, 3 });
    }
    if (m_vDirection == JVector2(1, 0)) // ¿À¸¥ÂÊ
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