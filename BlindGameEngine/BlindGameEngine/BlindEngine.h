#pragma once
class BlindEngine
{
	HWND m_WindowHandle;
	BlindRenderer * m_RenderManager;
	bool running = true;
	float DeltaTime = 0;
public:
	BlindEngine(HWND winHandle);
	~BlindEngine();
	void DebugUpdateCamera();

	void Run();
};

