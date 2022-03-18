#include "JSoundMgr.h"
void JSound::Play(bool bLoop)
{
	bool bPlay = false;
	if (m_pChannel != nullptr)
	{
		m_pChannel->isPlaying(&bPlay);
	}
	if (bPlay == false)
	{
		//채널은 플레이 사운드에서 반환이 되는 것 (사운드 제어를 담당)
		FMOD_RESULT ret = m_pSystem->playSound(m_pSound, nullptr, false, &m_pChannel);
		if (ret == FMOD_OK)
		{
			m_pChannel->setVolume(0.5f);
			if (bLoop)
				m_pChannel->setMode(FMOD_LOOP_NORMAL);
			else
				m_pChannel->setMode(FMOD_LOOP_OFF);
		}
	}

}
bool JSound::isPlaying()
{
	bool bPlay = false;
	if (m_pChannel != nullptr)
	{
		m_pChannel->isPlaying(&bPlay);
	}
	return bPlay;
}
void JSound::PlayEffect(bool bLoop)
{
	FMOD::Channel* pChannel = nullptr;
	//채널은 플레이 사운드에서 반환이 되는 것 (사운드 제어를 담당)
	FMOD_RESULT ret = m_pSystem->playSound(m_pSound, nullptr, false, &pChannel);
	if (ret == FMOD_OK)
	{
		m_pChannel->setVolume(0.5f);
		if (bLoop)
			m_pChannel->setMode(FMOD_LOOP_NORMAL);
		else
			m_pChannel->setMode(FMOD_LOOP_OFF);
	}

}
void JSound::Stop()
{
	if (m_pChannel != nullptr)
	{
		m_pChannel->stop();
	}
}

void JSound::Paused()
{
	bool bPlay = false;
	m_pChannel->isPlaying(&bPlay);
	if (bPlay)
	{
		bool paused;
		m_pChannel->getPaused(&paused);
		m_pChannel->setPaused(!paused);
	}
}

void JSound::VolumeUp(float fVolume)
{
	if (m_pChannel != nullptr)
	{
		float fCurrentVolume;
		m_pChannel->getVolume(&fCurrentVolume);
		m_fVolume = fCurrentVolume + fVolume;
		m_fVolume = max(0.0f, m_fVolume);
		m_fVolume = min(1.0f, m_fVolume);
		m_pChannel->setVolume(m_fVolume);
	}
}
void JSound::VolumeDown(float fVolume)
{
	if (m_pChannel != nullptr)
	{
		float fCurrentVolume;
		m_pChannel->getVolume(&fCurrentVolume);
		m_fVolume = fCurrentVolume - fVolume;
		m_fVolume = max(0.0f, m_fVolume);
		m_fVolume = min (1.0f, m_fVolume);
		m_pChannel->setVolume(m_fVolume);
	}
}
void JSound::Set(FMOD::System* pSystem, std::wstring filename, int iIndex)
{
	m_pSystem = pSystem;
	m_csName = filename;
	m_iIndex = iIndex;
}

bool JSound::Load(std::string filename)
{
	return true;
}


bool JSound::Init()
{
	return true;
}

bool JSound::Frame()
{
	if (m_pSound ==nullptr|| m_pChannel == nullptr) return true;

	unsigned int ms = 0;
	unsigned int size = 0;
	//길이
	m_pSound->getLength(&size, FMOD_TIMEUNIT_MS);
	//현재 플레이되는 위치
	m_pChannel->getPosition(&ms, FMOD_TIMEUNIT_MS);

	_stprintf_s(m_szBuffer, _T("전체시간[%02d:%02d:%02d]:경과시간[%02d:%02d:%02d]"),
		size / 1000 / 60,
		size / 1000 % 60,
		size / 10 % 60,
		ms / 1000 / 60,
		ms / 1000 % 60,
		ms / 10 % 60 );

	return true;
}

bool JSound::Render()
{
	return true;
}

bool JSound::Release()
{
	if (m_pSound) 
	{
		m_pSound->release();
		m_pSound = nullptr;
	}
	return true;
}


JSound::JSound()
{

}

JSound::~JSound()
{

	//m_pSound = nullptr;
	//m_pChannel = nullptr;
	//m_pSystem = nullptr;
}



JSound* JSoundMgr::Load(std::string filename)
{

	TCHAR szFileName[MAX_PATH] = { 0, };
	TCHAR Drive[MAX_PATH] = { 0, };
	TCHAR Dir[MAX_PATH] = { 0, };
	TCHAR FileName[MAX_PATH] = { 0, };
	TCHAR FileExt[MAX_PATH] = { 0, };

	std::wstring fullpathname = to_mw(filename);
	_tsplitpath_s(fullpathname.c_str(), Drive, Dir, FileName, FileExt);

	std::wstring name = FileName;
	name += FileExt;

	for (auto data : m_list)
	{
		if (data.second->m_csName == name)
		{
			return data.second.get();
		}
	}

	std::shared_ptr<JSound>pSound = std::make_shared<JSound>();
	
	FMOD_RESULT ret = m_pSystem->createSound(filename.c_str(), FMOD_DEFAULT, 0, &pSound->m_pSound);
	
	
	

	if (ret != FMOD_OK)
	{
		return nullptr;
	}
	m_list.insert(make_pair(name, pSound));
	
	pSound->Set(m_pSystem, name, m_iIndex);

	m_iIndex++;

	return pSound.get();
}

JSound* JSoundMgr::GetPtr(std::wstring csName)
{
	auto iter = m_list.find(csName);
	if (iter != m_list.end())
	{
		return (*iter).second.get();
	}
	return nullptr;

}


bool JSoundMgr::Init()
{
	FMOD_RESULT ret;
	ret = FMOD::System_Create(&m_pSystem);

	//동시에 터질 수 있는 이펙트 개수 32개로 지정한 것
	ret = m_pSystem->init(32, FMOD_INIT_NORMAL, 0);


	return true;
}

bool JSoundMgr::Frame()
{
	m_pSystem->update();
	//안녕하세요가 안~~~~녀엉하세요오오오 이런 식으로 늘어질수 잇어서 업데이트 사용
	return true;
}

bool JSoundMgr::Render()
{
	return true;
}

bool JSoundMgr::Release()
{
	for (auto data : m_list)
	{
		data.second->Release();
	}
	m_list.clear();
	m_pSystem->close();
	m_pSystem->release();
	return true;
}


JSoundMgr::JSoundMgr()
{
	m_iIndex = 0;
}

JSoundMgr::~JSoundMgr()
{

	//m_pSound = nullptr;
	//m_pChannel = nullptr;
	//m_pSystem = nullptr;
}
