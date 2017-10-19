#pragma once
#include <vector>

//Vertex layout
struct Vertex
{
	DirectX::XMFLOAT4 position;
	DirectX::XMFLOAT4 normal;
	DirectX::XMFLOAT4 uv;

	//Compare to verts
	bool operator==(Vertex v2)
	{
		return(
				position.x == v2.position.x &&
				position.y == v2.position.y &&
				position.z == v2.position.z &&
				position.w == v2.position.w &&

				uv.x == v2.uv.x &&
				uv.y == v2.uv.y &&
				uv.z == v2.uv.z &&
				uv.w == v2.uv.w &&

				normal.x == v2.normal.x &&
				normal.y == v2.normal.y &&
				normal.z == v2.normal.z &&
				normal.w == v2.normal.w
			);
	}
};

struct Mesh
{
	std::vector<Vertex> Verts;
	std::vector<uint32_t> Indices;
	
	//these are just references. The real pointers are cleaned up in renderer
	//for speed purposes

	ID3D11Buffer * m_VertBuffer = NULL;
	ID3D11Buffer * m_IndxBuffer = NULL;
};