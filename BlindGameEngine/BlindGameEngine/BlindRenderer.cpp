#include "stdafx.h"
#include "BlindRenderer.h"


void BlindRenderer::InitBackBuffer()
{
	//Gets the buffer for the texture that is used to render to the window, and saves a refernce to it in the pipeline
	m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&m_DefaultPipeline.m_BackBuffer);

	//Create the render target view for the back buffer
	m_Device->CreateRenderTargetView(m_DefaultPipeline.m_BackBuffer, NULL, &m_DefaultPipeline.m_RenderTargetView);

	//Set the render target to use
	//Can be post poned, but if not set again, this is better.
	//It also initializes the renderer with a target, in case of not setting later.
	m_Context->OMSetRenderTargets(1, &m_DefaultPipeline.m_RenderTargetView, NULL);

	//Get the rectangle of the window, for the size.
	RECT rectOfWindow;
	//GetWindowRect - Returns the window size, with the boarder, and the title bar.
	//GetClientRect - Returns the windows actual space.
	GetClientRect(m_WinHandle, &rectOfWindow);
	//Difference of the two, give the the width/height of the window.
	//because values are in screen space
	m_winWidth = rectOfWindow.right - rectOfWindow.left;
	m_winHeight = rectOfWindow.bottom - rectOfWindow.top;

	//Setup the view port.
	m_Viewport.TopLeftX = 0;
	m_Viewport.TopLeftY = 0;
	m_Viewport.Width = m_winWidth;
	m_Viewport.Height = m_winHeight;
	m_Viewport.MinDepth = 0;
	m_Viewport.MaxDepth = 1;

}

void BlindRenderer::InitDepthBuffer()
{
	//Describes how the texture is stored, read from, and written to

	//The long way. ===================================
	//D3D11_TEXTURE2D_DESC depthDesc;
	//ZeroMemory(&depthDesc, sizeof(depthDesc));
	////Setup the size of the texture
	//depthDesc.Width = m_winWidth;
	//depthDesc.Height = m_winHeight;
	////topic for another day.
	//depthDesc.MipLevels = 1;
	////Only one texture within the buffer.
	//depthDesc.ArraySize = 1;
	////Sets up the texture to use all 32 bits of one pixel, to define one color of a typeless nature
	////When used for a depth buffer, this will convert the 32bits into a float
	//depthDesc.Format = DXGI_FORMAT_R32_TYPELESS;
	////Quality level definitions of the texture
	//depthDesc.SampleDesc.Count= 0;
	//depthDesc.SampleDesc.Quality = 0;
	////Default, because we are using the texture, as a texture.
	//depthDesc.Usage = D3D11_USAGE_DEFAULT;
	////Define it as a depth stencil, but also as a shader resource in case we use it for shadow mapping
	//depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	////CPU doesn't need access to this flag
	//depthDesc.CPUAccessFlags = 0;
	////no flags for this.
	//depthDesc.MiscFlags = 0;
	//==================================================


	//Describes how the texture is made using the predefined class structure for default values.
	CD3D11_TEXTURE2D_DESC premadeDesc(DXGI_FORMAT_D24_UNORM_S8_UINT, m_winWidth, m_winHeight, 1, 0, D3D11_BIND_DEPTH_STENCIL);

	m_Device->CreateTexture2D(&premadeDesc, NULL, &m_DefaultPipeline.m_DepthStencilBuffer);
}

void BlindRenderer::InitDepthView()
{
	//Creates the view used for the depth stencil
	CD3D11_DEPTH_STENCIL_VIEW_DESC desc(D3D11_DSV_DIMENSION_TEXTURE2D);
	m_Device->CreateDepthStencilView(m_DefaultPipeline.m_DepthStencilBuffer, &desc, &m_DefaultPipeline.m_DepthStencilView);
}

void BlindRenderer::InitShaders()
{
	//Sets up the shaders from the shader headerfiles.
	//This is a temperary way of doing things until we get more advanced shaders
	m_Device->CreateVertexShader(&TrivialVS, sizeof(TrivialVS), NULL, &m_DefaultPipeline.m_VertexShader);
	m_Device->CreatePixelShader(&TrivialPS, sizeof(TrivialPS), NULL, &m_DefaultPipeline.m_PixelShader);
}

void BlindRenderer::InitViewProjMatrix()
{
	//Aspect ratio for the window area, used in perspective matrix
	float AspectRatio = (float)m_winWidth/m_winHeight;
	//Calculate field of view angle
	float FoV = 70.0f * DirectX::XM_PI / 180.0f;
	//Create the perspective Matrix
	DirectX::XMMATRIX prespectiveMatrix = DirectX::XMMatrixPerspectiveFovLH(FoV, AspectRatio, 0.01f, 100.0f);
	//Copy the matrix into the float4x4 for storage.
	DirectX::XMStoreFloat4x4(&m_ProjMatrix, prespectiveMatrix);
	DirectX::XMStoreFloat4x4(&m_WVPData.proj, DirectX::XMMatrixTranspose(prespectiveMatrix));
	//Where the camera is located
	static const DirectX::XMVECTORF32 eye = { 0.5f, 1.0f, -2.0f, 0.0f };
	//What the camera is looking at
	static const DirectX::XMVECTORF32 at = { 0,0,0,0 };
	//World UP vector
	static const DirectX::XMVECTORF32 up = { 0,1,0,0 };

	//Build a view matrix for the camera
	DirectX::XMMATRIX viewMat = DirectX::XMMatrixLookAtLH(eye, at, up);
	DirectX::XMStoreFloat4x4(&m_ViewMatrix, DirectX::XMMatrixTranspose(viewMat));
	//DirectX::XMStoreFloat4x4(&m_WVPData.view, DirectX::XMMatrixTranspose(viewMat));
	
	//Inverse the view matrix to get the camera matrix
	viewMat = DirectX::XMMatrixInverse(NULL, viewMat);
	//Store the camera matrix in a float4x4
	DirectX::XMStoreFloat4x4(&m_Camera, viewMat);

}

//DEPRECTED
void BlindRenderer::BuildVertexBuffer(Mesh * m)
{
	
	CD3D11_BUFFER_DESC desc(sizeof(Vertex) * m->Verts.size() , D3D11_BIND_VERTEX_BUFFER, D3D11_USAGE_IMMUTABLE, 0);
	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = m->Verts.data();
	m_Device->CreateBuffer(&desc, &data, &m->m_VertBuffer);
}

void BlindRenderer::SetupInputLayout()
{
	//Setup input layout based on the Vertex Structure

	D3D11_INPUT_ELEMENT_DESC desc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "UV", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	m_Device->CreateInputLayout(desc, ARRAYSIZE(desc), TrivialVS, sizeof(TrivialVS), &m_DefaultPipeline.m_InputLayout);
}

BlindRenderer::BlindRenderer(HWND winHandle)
{
	m_WinHandle = winHandle;
}

BlindRenderer::~BlindRenderer()
{
	//TODO Clean up all Direct X memory.
	//Clear the state of the context, so it isn't referencing the buffers/shaders/whatever
	m_Context->ClearState();
	//Do this in the opposite order of creation preferably, could cause issues if done otherwise.
	m_DefaultPipeline.m_RasterizerState->Release();
	m_DefaultPipeline.m_InputLayout->Release();

	//m_TriangleBuffer->Release();
	m_WVPConstantBuffer->Release();

	m_DefaultPipeline.m_VertexShader->Release();
	m_DefaultPipeline.m_PixelShader->Release();

	m_DefaultPipeline.m_RenderTargetView->Release();
	m_DefaultPipeline.m_BackBuffer->Release();
	m_DefaultPipeline.m_DepthStencilView->Release();
	m_DefaultPipeline.m_DepthStencilBuffer->Release();

	m_Context->Release();
	m_SwapChain->Release();
	m_Device->Release();
}

//DEPRECTED
void BlindRenderer::Render()
{
	//This function renders a triangle.
	//Color to clear render target to


	//float clearcolor[4] = { 0.0f, 0.0f, 1.0f, 0.0f };
	////Clear out the depth stencil, and the render target
	//m_Context->ClearDepthStencilView(m_DefaultPipeline.m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	//m_Context->ClearRenderTargetView(m_DefaultPipeline.m_RenderTargetView, clearcolor);
	//m_Context->RSSetViewports(1,&m_Viewport);
	//
	////setup constant buffer with data.
	//m_WVPData.view = m_ViewMatrix;
	////DirectX::XMStoreFloat4x4(&m_WVPData.view, DirectX::XMMatrixTranspose(DirectX::XMMatrixInverse(nullptr, DirectX::XMLoadFloat4x4(&m_Camera))));
	//m_Context->UpdateSubresource(m_WVPConstantBuffer, 0, NULL, &m_WVPData, 0, 0);
	//
	////set rasterizer state
	//m_Context->RSSetState(m_DefaultPipeline.m_RasterizerState);
	////Set vertex shader
	//m_Context->VSSetShader(m_DefaultPipeline.m_VertexShader, 0, 0);
	//m_Context->VSSetConstantBuffers(0, 1, &m_WVPConstantBuffer);
	////set pixel shader
	//m_Context->PSSetShader(m_DefaultPipeline.m_PixelShader, 0, 0);
	////Set input layout
	//m_Context->IASetInputLayout(m_DefaultPipeline.m_InputLayout);
	////Set topology
	//m_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	////How large in memory each vertex is for drawing
	//unsigned int stride = sizeof(Vertex);
	////Offsets between verts
	//unsigned int offset = 0;
	//m_Context->IASetVertexBuffers(0,1, &m_TriangleBuffer, &stride, &offset);
	////Draw the first 3 verts in the vertex buffer
	//m_Context->Draw(3, 0);
	////Present the finished screen onto the window
	//m_SwapChain->Present(0, 0);
}

DirectX::XMFLOAT4X4 BlindRenderer::GetCamera()
{
	return m_Camera;
}

void BlindRenderer::SetCamera(DirectX::XMFLOAT4X4 cam)
{
	//Set camera
	m_Camera = cam;
	//Set View Matrix
	
	//Inverse the matrix before setting it because the view matrix 
	//is the opposite of the camera matrix
	DirectX::XMMATRIX mat = DirectX::XMLoadFloat4x4(&m_Camera);
	
	mat = DirectX::XMMatrixTranspose(DirectX::XMMatrixInverse(NULL, mat));
	DirectX::XMStoreFloat4x4(&m_ViewMatrix, mat);

}

void BlindRenderer::InitRenderer()
{
	//The descriptor for setting up the swap chain
	DXGI_SWAP_CHAIN_DESC SwapChainDesc;
	//sets all values to 0, so we don't have garbage memory.
	ZeroMemory(&SwapChainDesc, sizeof(SwapChainDesc));
	//Texture Buffers.
	//How many buffers to create
	SwapChainDesc.BufferCount = 1;
	//the Format of the buffer to use
	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//What the buffer is used for (in this case, render target.)
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	//the target window handle to render the resulting texture buffer to
	SwapChainDesc.OutputWindow = m_WinHandle;
	//Buffer sampler count.
	SwapChainDesc.SampleDesc.Count = 1;
	//Windowed mode.
	SwapChainDesc.Windowed = true;


	//DEBUG 
	//Setup the device, swap chain, and context.
	D3D11CreateDeviceAndSwapChain(NULL, //which hardward device to use, defaults to first in list.
		D3D_DRIVER_TYPE_HARDWARE, //
		NULL,
		D3D11_CREATE_DEVICE_DEBUG,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&SwapChainDesc,
		&m_SwapChain,
		&m_Device,
		NULL,
		&m_Context
	);

	InitBackBuffer();
	InitDepthBuffer();
	InitDepthView();

	//Setup the Rasterizer
	D3D11_RASTERIZER_DESC RasterDesc;
	ZeroMemory(&RasterDesc, sizeof(RasterDesc));
	//Cull mode - when to ignore faces on a model
	RasterDesc.CullMode = D3D11_CULL_BACK; // D3D11_CULL_NONE, D3D11_CULL_FRONT
	//Fill Mode - Defines whether to fill in the triangles of the model
	RasterDesc.FillMode = D3D11_FILL_SOLID; // D3D11_FILL_WIREFRAME
	//Create the rasterizer with the description
	m_Device->CreateRasterizerState(&RasterDesc, &m_DefaultPipeline.m_RasterizerState);

	InitShaders();
	InitViewProjMatrix();
	SetupInputLayout();

	//Setup the constant buffer
	CD3D11_BUFFER_DESC constantBufferDesc(sizeof(WorldViewProj), D3D11_BIND_CONSTANT_BUFFER);
	m_Device->CreateBuffer(&constantBufferDesc, NULL, &m_WVPConstantBuffer);

	DirectX::XMStoreFloat4x4(&m_WVPData.worldMatrix, DirectX::XMMatrixTranspose( DirectX::XMMatrixIdentity()));

}

void BlindRenderer::Render(Mesh * m)
{

	float clearcolor[4] = { 0.0f, 0.0f, 1.0f, 0.0f };
	//Clear out the depth stencil, and the render target
	m_Context->ClearDepthStencilView(m_DefaultPipeline.m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	m_Context->ClearRenderTargetView(m_DefaultPipeline.m_RenderTargetView, clearcolor);
	m_Context->RSSetViewports(1, &m_Viewport);

	//setup constant buffer with data.
	m_WVPData.view = m_ViewMatrix;
	//DirectX::XMStoreFloat4x4(&m_WVPData.view, DirectX::XMMatrixTranspose(DirectX::XMMatrixInverse(nullptr, DirectX::XMLoadFloat4x4(&m_Camera))));
	m_Context->UpdateSubresource(m_WVPConstantBuffer, 0, NULL, &m_WVPData, 0, 0);

	//set rasterizer state
	m_Context->RSSetState(m_DefaultPipeline.m_RasterizerState);
	//Set vertex shader
	m_Context->VSSetShader(m_DefaultPipeline.m_VertexShader, 0, 0);
	m_Context->VSSetConstantBuffers(0, 1, &m_WVPConstantBuffer);
	//set pixel shader
	m_Context->PSSetShader(m_DefaultPipeline.m_PixelShader, 0, 0);
	//Set input layout
	m_Context->IASetInputLayout(m_DefaultPipeline.m_InputLayout);
	//Set topology
	m_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//How large in memory each vertex is for drawing
	unsigned int stride = sizeof(Vertex);
	//Offsets between verts
	unsigned int offset = 0;
	m_Context->IASetVertexBuffers(0, 1, &m->m_VertBuffer, &stride, &offset);
	//Draw the first 3 verts in the vertex buffer
	m_Context->Draw(m->Verts.size(), 0);
	//Present the finished screen onto the window
	m_SwapChain->Present(0, 0);
}
