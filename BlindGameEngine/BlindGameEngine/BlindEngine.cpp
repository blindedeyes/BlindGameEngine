#include "stdafx.h"
#include "BlindEngine.h"
#include <chrono>

BlindEngine::BlindEngine(HWND winHandle)
{
	m_WindowHandle = winHandle;
	m_RenderManager = new BlindRenderer(m_WindowHandle);
	m_RenderManager->InitRenderer();
}

BlindEngine::~BlindEngine()
{
	//Delete in order to call destructor, and to clean up the renderer memory.
	delete m_RenderManager;
}

void BlindEngine::DebugUpdateCamera()
{
	//Get the current camera of the renderer
	DirectX::XMFLOAT4X4 cam = m_RenderManager->GetCamera();
	DirectX::XMMATRIX matCam = DirectX::XMLoadFloat4x4(&cam);
	//Perform math.
	if (GetAsyncKeyState('W'))
	{
		matCam =  DirectX::XMMatrixTranslation(0, 0, 1 * DeltaTime)* matCam;
	}
	if (GetAsyncKeyState('S'))
	{
		matCam = DirectX::XMMatrixTranslation(0, 0, -1 * DeltaTime)* matCam;
	}
	if (GetAsyncKeyState('D'))
	{
		matCam = DirectX::XMMatrixTranslation(1 * DeltaTime, 0, 0)* matCam;
	}
	if (GetAsyncKeyState('A'))
	{
		matCam = DirectX::XMMatrixTranslation(-1 * DeltaTime, 0, 0)* matCam;
	}

	DirectX::XMStoreFloat4x4(&cam, matCam);
	m_RenderManager->SetCamera(cam);
}

void BlindEngine::Run()
{
	std::chrono::time_point<std::chrono::system_clock> start;
	start = std::chrono::system_clock::now();

	DebugUpdateCamera();
	m_RenderManager->Render();
	DeltaTime = (float)(std::chrono::system_clock::now() - start).count() / 1e7f;
}
