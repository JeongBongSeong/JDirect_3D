#include "JTileObj2D.h"



void JTileObj2D::HitOverlap(JBaseObject* pObj, DWORD dwState)
{
    
    if (dwState == JCollisionType::Overlap)
    {
        //pObj->m_bDead = true;
        //m_bDead = true;
        //

        //Å¸°ÙÅÊÅ©À§Ä¡ Æø¹ß ÀÌÆåÆ® 
        
        //pObj->m_fSpeed = 0;
        //pObj->m_vPos
        pObj->m_fSpeed = 0;
    }
    
}

void JTileObj2D::SetEffect()
{
}


void JTileObj2D::SettingPosition(JVector2* pos, JVector2* dir)
{
    m_vPos = *pos;
    m_vDirection = *dir;
}
bool JTileObj2D::Frame()
{
    if (m_bDead == true) return false;


    
    return true;
}

JTileObj2D::JTileObj2D()
{
    m_vDirection = JVector2(0, -1);
    m_fSpeed = 0.0f; //50.0f;
    m_dwCollisionType = JCollisionType::Overlap;
    m_dwSelectType = JSelectType::Select_Overlap;
}

JTileObj2D::~JTileObj2D()
{
}