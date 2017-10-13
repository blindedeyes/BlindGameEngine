#include "stdafx.h"
#include "Object.h"
#include "Component.h"

void Object::Update()
{
	for each (auto comp in m_Components)
	{
		comp->Update();
	}
}

void Object::Start()
{
	for each (auto comp in m_Components)
	{
		comp->Start();
	}
}

void Object::CollisionUpdate()
{
	/*for each (auto comp in m_Components)
	{
		comp->Update();
	}*/
}

void Object::FixedUpdate()
{
	for each (auto comp in m_Components)
	{
		comp->FixedUpdate();
	}
}
