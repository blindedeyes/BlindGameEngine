#pragma once
#include <vector>
//Vertex layout
struct Vertex
{
	DirectX::XMFLOAT4 position;
	DirectX::XMFLOAT4 normal;
	DirectX::XMFLOAT4 uv;
};

struct Mesh
{
	std::vector<Vertex> Verts;
	ID3D11Buffer * m_VertBuffer = NULL;
};