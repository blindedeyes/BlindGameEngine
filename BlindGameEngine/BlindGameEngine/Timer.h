#pragma once
#include <chrono>
class Time;
class Timer
{
	//Time since last
	float m_elpseTime;
	//Target time
	float m_targetTime;
	//time class reference
	Time * m_time;
public:
	Timer(float TargetTime);
	~Timer();
	//Adds delta time to it
	//Use: time in steps of frames
	void Step();
	//Adds Unscaled delta time
	//Use: time in steps of frames
	void UnscaledStep();
	//Sets elpsTime to delta since start of frame.
	//Use: during frame time steps
	void SubStep();
	//Sets elpsTime to delta since start of frame.
	//Use: during frame time steps
	void UnscaledSubStep();
	//resets elps time to 0
	void Reset();
	//sets elps time to (elps - target), so it can be done in a loop, or the like
	void IncrementalReset();
	//sets target time?
	void SetTargetTime(float TargetTime);
	//returns the elps time?
	float getElpsTime();
	//Returns if the timer has reached the end
	bool isTimerUp();
};