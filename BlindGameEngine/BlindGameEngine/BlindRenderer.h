#pragma once
//Direct X 11 Header file.
#include <d3d11.h>
#include "Pipeline.h"
#include "TrivialVS.h"
#include "TrivialPS.h"

//Vertex layout
struct Vertex
{
	DirectX::XMFLOAT4 position;
	DirectX::XMFLOAT4 normal;
	DirectX::XMFLOAT4 uv;
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

	ID3D11Buffer * m_TriangleBuffer;

	unsigned int m_winWidth, m_winHeight;

	void InitBackBuffer();
	void InitDepthBuffer();
	void InitDepthView();
	void InitShaders();
	void InitViewProjMatrix();

	void BuildTriangle();
	
	void SetupInputLayout();

public:
	BlindRenderer(HWND winHandle);
	~BlindRenderer();

	void Render();

	//Setup the rendering Device, Swap chain, and context
	void InitRenderer();
};
