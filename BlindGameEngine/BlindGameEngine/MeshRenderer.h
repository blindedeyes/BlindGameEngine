#pragma once
#include "Component.h"
struct Mesh;
class MeshRenderer :
	public Component
{
	Mesh * m_Mesh;
	
public:
	MeshRenderer(Mesh * m);
	~MeshRenderer();

	void Start() override;
	void Destroy() {}
	void Update() {}
	void FixedUpdate() {}

	const Mesh * const GetMesh();
};

