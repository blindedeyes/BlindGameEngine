#include "stdafx.h"
#include "MeshRenderer.h"
#include "Object.h"

MeshRenderer::MeshRenderer(Mesh* m)
{
}


MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::Start()
{
	m_GameObject->m_MeshRenderer = this;
}

const Mesh * const MeshRenderer::GetMesh()
{
	return m_Mesh;
}
