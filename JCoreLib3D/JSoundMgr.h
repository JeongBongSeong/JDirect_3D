#pragma once
#include "JStd.h"
#include "fmod.hpp"
#include "fmod_errors.h"
#pragma comment(lib,"fmod_vc.lib")

class JSound
{
public:
	int m_iIndex;
	std::wstring m_csName;
	FMOD::Sound* m_pSound = nullptr;
	FMOD::Channel* m_pChannel = nullptr;
	FMOD::System* m_pSystem = nullptr;
	float m_fVolume;
	TCHAR m_szBuffer[256];
public:
	void Set(FMOD::System* pSystem,std::wstring filename, int iIndex);
	bool Load(std::string filename);
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	void Play(bool bLoop=false);
	bool isPlaying();
	void PlayEffect(bool bLoop=false);
	void Stop();
	void Paused();
	void VolumeUp(float fVolume = 0.1);
	void VolumeDown(float fVolume = 0.1);
public:
	JSound();
	virtual ~JSound();
};

class JSoundMgr : public JSingleton<JSoundMgr>
{
private:
	int m_iIndex;
public:
	friend class JSingleton<JSoundMgr>;
	std::map<std::wstring, std::shared_ptr<JSound>> m_list;
	FMOD::System* m_pSystem = nullptr;
public:
	JSound* Load(std::string filename);
	JSound* GetPtr(std::wstring csName);
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
private:
	JSoundMgr();
public:
	virtual ~JSoundMgr();
};

#define I_Sound JSoundMgr::Get()