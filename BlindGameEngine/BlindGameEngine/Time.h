#pragma once
#include <chrono>

//Simple timer class, times are all in seconds.
class Time
{
	float m_deltaTime;
	float m_unscaleDeltaTime;
	float m_timeScale;

	std::chrono::time_point<std::chrono::system_clock> m_lastnow;
	std::chrono::time_point<std::chrono::system_clock> m_applicationStart;
public:
	Time();
	~Time();

	void Restart();
	void Step();
	
	float GetDeltaTime();
	float GetUnscaledDeltaTime();
	float SetTimeScale();

};

