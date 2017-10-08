#pragma once
class Time;
class BlindEngine
{
	HWND m_WindowHandle;
	BlindRenderer * m_RenderManager;
	bool running = true;
	float DeltaTime = 0;


	POINT mLastPoint;
	
	Mesh* temp;
	Time* m_time;
	//float posX, posY;
public:
	BlindEngine(HWND winHandle);
	~BlindEngine();

	void DebugUpdateCamera();
	void Run();
};