#include "stdafx.h"
#include "BlindEngine.h"


BlindEngine::BlindEngine(HWND winHandle)
{
	m_WindowHandle = winHandle;
	m_RenderManager = new BlindRenderer(m_WindowHandle);
	m_RenderManager->InitRenderer();
}

BlindEngine::~BlindEngine()
{
}

void BlindEngine::Run()
{
	m_RenderManager->Render();

}
