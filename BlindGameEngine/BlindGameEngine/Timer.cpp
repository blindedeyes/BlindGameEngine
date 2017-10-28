#include "stdafx.h"

#include "Timer.h"
#include "Time.h"

Timer::Timer(float TargetTime)
{
	m_targetTime = TargetTime;
	m_time = Time::GetInstance();
}

Timer::~Timer()
{
}

void Timer::Step()
{
	m_elpseTime += m_time->GetDeltaTime();
}

void Timer::UnscaledStep()
{
	m_elpseTime += m_time->GetUnscaledDeltaTime();

}

void Timer::SubStep()
{
	m_elpseTime = m_time->GetTimeSinceLastNow();
}

void Timer::UnscaledSubStep()
{
	m_elpseTime = m_time->GetUnscaledTimeSinceLastNow();
}



void Timer::Reset()
{
	m_elpseTime = 0;
}

void Timer::IncrementalReset()
{
	m_elpseTime -= m_targetTime;
}

void Timer::SetTargetTime(float TargetTime)
{
	m_targetTime = TargetTime;
}

float Timer::getElpsTime()
{
	return m_elpseTime;
}

bool Timer::isTimerUp()
{
	return (m_elpseTime > m_targetTime);
}