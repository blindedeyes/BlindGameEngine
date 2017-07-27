#pragma once

//Describes the current state of rendering.
struct Pipeline
{
	//Texture that is eventually rendered to the screen
	ID3D11Texture2D * m_BackBuffer;
	//The View used to access what is currently rendered.
	ID3D11RenderTargetView * m_RenderTargetView;

	//Depth Buffer used for rendering things on top of eachother
	ID3D11Texture2D * m_DepthStencilBuffer;
	ID3D11DepthStencilState * m_DepthStencilState;
	//The view used to access the current depth buffer.
	ID3D11DepthStencilView * m_DepthStencilView;
	//Describes how to draw objects
	ID3D11RasterizerState * m_RasterizerState;

	//Describes how object data is layed out
	ID3D11InputLayout * m_InputLayout;

	//reference to the shaders to use when drawing.
	ID3D11PixelShader * m_PixelShader;
	ID3D11VertexShader * m_VertexShader;
};

