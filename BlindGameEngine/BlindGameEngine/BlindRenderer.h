#pragma once
//Direct X 11 Header file.
#include "Pipeline.h"
#include "TrivialVS.h"
#include "TrivialPS.h"

class ObjectManager;

//Costant Buffer
struct WorldViewProj
{
	DirectX::XMFLOAT4X4 view;
	DirectX::XMFLOAT4X4 proj;
	DirectX::XMFLOAT4X4 worldMatrix;
};

//Blind game engine renderer Class
//Initialized the DirectX pipeline
//and is used to draw the objects 
//to the screen
class BlindRenderer
{
	//Handle for the window
	HWND m_WinHandle;
	//The gpu, or whatever method is used to draw
	ID3D11Device * m_Device;
	//Holds data about how rendering works
	IDXGISwapChain * m_SwapChain;
	//Actually used to create Buffers and draw
	ID3D11DeviceContext * m_Context;

	//Default pipeline to use in rendering
	Pipeline m_DefaultPipeline;

	D3D11_VIEWPORT m_Viewport;

	DirectX::XMFLOAT4X4 m_Camera;
	DirectX::XMFLOAT4X4 m_ViewMatrix;
	DirectX::XMFLOAT4X4 m_ProjMatrix;

	

	WorldViewProj m_WVPData;
	ID3D11Buffer * m_WVPConstantBuffer;
	unsigned int m_winWidth, m_winHeight;

	void InitBackBuffer();
	void InitDepthBuffer();
	void InitDepthView();
	void InitShaders();
	void InitViewProjMatrix();


	void SetupInputLayout();

public:
	BlindRenderer(HWND winHandle);
	~BlindRenderer();

	DirectX::XMFLOAT4X4 GetCamera();
	void SetCamera(DirectX::XMFLOAT4X4);
	//Setup the rendering Device, Swap chain, and context
	void InitRenderer();
	
	void ClearPipelineViews(Pipeline* p);
	void Present();

	void BuildVertexBuffer(Mesh * m);
	void BuildIndexBuffer(Mesh * m);

	void RenderScene(ObjectManager* objMan);
	void RenderMesh(Mesh* m);
};

