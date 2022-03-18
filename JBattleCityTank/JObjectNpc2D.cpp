#include "JObjectNpc2D.h"


void JObjectNpc2D::HitOverlap(JBaseObject* pObj, DWORD dwState)
{
    if (dwState == JCollisionType::Overlap)
    {
        //pObj->m_bAlphaBlend = !pObj->m_bAlphaBlend;
    }
}

void JObjectNpc2D::HitSelect(JBaseObject* pObj, DWORD dwState)
{
    if (m_dwSelectState & J_HOVER)
    {
        INT K = 0;
    }
    if (m_dwSelectState & J_FOCUS)
    {
        INT K = 0;
    }
    if (m_dwSelectState & J_ACTIVE)
    {
        INT K = 0;
    }
    if (m_dwSelectState & J_SELECTED)
    {
        INT K = 0;
        //m_bSelect = true;
        //m_bDead = true;
    }
}

void JObjectNpc2D::Anime(JVector2 pos)
{
    m_fChangeTime = m_pSprite->m_fAnimTime / m_pSprite->m_rtArray.size();
    m_fTimer += g_fSecPerFrame;
    if (m_fTimer >= m_fChangeTime)
    {
        m_iCurrentIndex++;
        if (m_iCurrentIndex >= m_pSprite->m_rtArray.size())
        {
            m_iCurrentIndex = 0;
            //m_bDead = true;
        }
        m_fTimer -= m_fChangeTime;
        SetRectSource(m_pSprite->m_rtArray[m_iCurrentIndex]);

    }
    AddPosition(pos);
}
bool JObjectNpc2D::Frame()
{
    m_NpcAttackExplosionObj.SetTargetPosition(&m_vPos);
    
    JVector2 pos;
    JVector2 p;
    if (m_vPos.x > m_rtIngame.right - 30.0f)
    {
        m_vDirection.x = m_vDirection.x * -1.0f;
        m_vPos.x = m_rtIngame.right - 30.0f;
    }
    if (m_vPos.x < m_rtIngame.left + 30.0f)
    {
        m_vDirection.x = m_vDirection.x * -1.0f;
        m_vPos.x = m_rtIngame.left + 30.0f;
    }
    if (m_vPos.y > m_rtIngame.bottom - 30.0f)
    {
        m_vDirection.y = m_vDirection.y * -1.0f;
        m_vPos.y = m_rtIngame.bottom - 30.0f;
    }
    if (m_vPos.y < m_rtIngame.top + 30.0f)
    {
        m_vDirection.y = m_vDirection.y * -1.0f;
        m_vPos.y = m_rtIngame.top + 30.0f;
    }
    if (m_bCheck)
    {
        m_NpcAttackExplosionObj.m_bDead = false;
        m_bDead = true;
        m_bCheck = false;
    }
    m_NpcAttackExplosionObj.Frame();
    pos = m_vDirection * (m_fSpeed * g_fSecPerFrame);
    //Anime(pos);
    AddPosition(pos);
    return true;
}
bool JObjectNpc2D::Render()
{
    m_NpcAttackExplosionObj.Render();
    JObject2D::Render();
    return true;
}
JObjectNpc2D::JObjectNpc2D()
{
    
    m_vDirection.x = 0;
    m_vDirection.y = 0;
    m_fSpeed = 20.0f + (rand() % 300); //50.0f;
    m_dwCollisionType = JCollisionType::Overlap;
    m_dwSelectType = JSelectType::Select_Overlap;
}

JObjectNpc2D::~JObjectNpc2D()
{
}
