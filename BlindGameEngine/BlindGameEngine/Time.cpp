#include "stdafx.h"
#include "Time.h"


Time::Time()
{
	m_lastnow = std::chrono::system_clock::now();
}


Time::~Time()
{
}

void Time::Restart()
{
	m_lastnow = std::chrono::system_clock::now();
	m_deltaTime = 0;
	m_unscaleDeltaTime = 0;
}

void Time::Step()
{
	m_unscaleDeltaTime = ((float)((std::chrono::system_clock::now() - m_lastnow).count()) / 1e7f);
	m_deltaTime = m_unscaleDeltaTime*m_timeScale;
	m_lastnow = std::chrono::system_clock::now();
}

float Time::GetDeltaTime()
{
	return m_deltaTime;
}

float Time::GetUnscaledDeltaTime()
{
	return m_unscaleDeltaTime;
}

float Time::SetTimeScale()
{
	return m_timeScale;
}

Time * Time::GetInstance()
{
	static Time* t;
	if (!t)
		t = new Time();
	return t;
}
