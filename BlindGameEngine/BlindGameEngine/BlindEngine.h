#pragma once
class BlindEngine
{
	HWND m_WindowHandle;
	BlindRenderer * m_RenderManager;
	bool running = true;
public:
	BlindEngine(HWND winHandle);
	~BlindEngine();

	void Run();
};

