#pragma once
#include "Timer.h"

class Time;
class ObjectManager;
class BlindEngine
{
	HWND m_WindowHandle;
	BlindRenderer * m_RenderManager;
	bool running = true;
	float DeltaTime = 0;


	POINT mLastPoint;
	
	Mesh* temp;
	Time* m_time;
	Timer* m_FixedTimer;
	ObjectManager* m_ObjectManager;
	//float posX, posY;
public:
	BlindEngine(HWND winHandle);
	~BlindEngine();

	void DebugUpdateCamera();
	int Run();
};