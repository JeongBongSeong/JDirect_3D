#include "JIntroWorld.h"

bool JIntroWorld::Init()
{
	return true;
}
bool JIntroWorld::Load(std::wstring filename)
{
	//»ç¿îµå
	m_pBackGroundMusic = I_Sound.Load("..\\..\\data\\Sound\\BattleCity\\BattleCityBGM.mp3");
	//I_Sound.GetPtr(pSound->m_csName)->Play();
	m_pBackGroundMusic->Play(true);

    return true;
}

bool JIntroWorld::Frame()
{
	m_pBackGroundMusic->Frame();
    return true;
}

bool JIntroWorld::Render()
{
	return true;
}

bool JIntroWorld::Release()
{
    return true;
}
