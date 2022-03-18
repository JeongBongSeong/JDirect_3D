#pragma once
#include"JObject2D.h"

class JUIObject : public JObject2D
{
public:
	bool Frame() override;
	bool Render() override;
};


class JImageObject : public JUIObject
{
public:
	float m_fAlpha = 0.0f;
	bool m_bFadeIn = false;
	bool m_bFadeOut = false;
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	void FadeIn();
	void FadeOut();
};

class JButtonObject : public JUIObject
{
public:
	bool Frame() override;
	bool Render() override;
};

