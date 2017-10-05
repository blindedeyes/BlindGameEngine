#include "stdafx.h"
#include "BlindEngine.h"
#include <chrono>

BlindEngine::BlindEngine(HWND winHandle)
{
	m_WindowHandle = winHandle;
	m_RenderManager = new BlindRenderer(m_WindowHandle);
	m_RenderManager->InitRenderer();
	DataManager dataman;
	temp = dataman.LoadMesh("Cube.fbx");
	m_RenderManager->BuildVertexBuffer(temp);
	m_RenderManager->BuildIndexBuffer(temp);
	GetCursorPos(&mLastPoint);
}

BlindEngine::~BlindEngine()
{
	//Delete in order to call destructor, and to clean up the renderer memory.
	delete m_RenderManager;
}
//This function WILL be removed later
// TODO : remove later, with script based movement.
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
	if (GetAsyncKeyState(VK_SPACE))
	{
		matCam = DirectX::XMMatrixTranslation(0, 1 * DeltaTime, 0)* matCam;
	}
	if (GetAsyncKeyState(VK_SHIFT))
	{
		matCam = DirectX::XMMatrixTranslation(0,-1 * DeltaTime, 0)* matCam;
	}
	DirectX::XMStoreFloat4x4(&cam, matCam);

	//Local Rotation
	POINT cPoint;
	GetCursorPos(&cPoint);
	if (GetAsyncKeyState(VK_RBUTTON))
	{
		//If holding right click, then lets rotate the camera.
		float rotSpd = 5.0f;
		float deltaX = (float)(cPoint.x - mLastPoint.x),
			deltaY = (float)(cPoint.y - mLastPoint.y);
		//extract camera pos, and store it for later.
		DirectX::XMFLOAT4 pos = DirectX::XMFLOAT4(cam._41, cam._42, cam._43, cam._44);
		//Remove pos.
		cam._41 = 0;
		cam._42 = 0;
		cam._43 = 0;
		//merge both the rotations into one matrix.
		DirectX::XMMATRIX rot = DirectX::XMMatrixRotationX(deltaY * rotSpd * DeltaTime) * DirectX::XMMatrixRotationY(deltaX*rotSpd*DeltaTime);
		//Load camera into a matrix again
		matCam = DirectX::XMLoadFloat4x4(&cam);
		//Mult rotation into camera
		matCam = rot*matCam;
		DirectX::XMStoreFloat4x4(&cam, matCam);
		//Remove pos.
		//Remove pos.
		cam._41 = pos.x;
		cam._42 = pos.y;
		cam._43 = pos.z;

	}
	mLastPoint = cPoint;
	m_RenderManager->SetCamera(cam);
}

void BlindEngine::Run()
{
	std::chrono::time_point<std::chrono::system_clock> start;
	start = std::chrono::system_clock::now();
	//Clear screen
	DebugUpdateCamera();

	m_RenderManager->ClearPipelineViews(NULL);
	m_RenderManager->Render(temp);
	m_RenderManager->Present();
	DeltaTime = (float)(std::chrono::system_clock::now() - start).count() / 1e7f;
}
