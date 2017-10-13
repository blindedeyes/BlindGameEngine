#include "stdafx.h"
#include "ObjectManager.h"
#include "Object.h"

ObjectManager::ObjectManager()
{
}


ObjectManager::~ObjectManager()
{
}

void ObjectManager::RemoveObject(Object * o)
{
}

void ObjectManager::AddObject(Object * o)
{
	if (!o->isStatic())
		m_dynamic.push_back(o);
	else
		m_static.push_back(o);

	m_allObjects.push_back(o);
}

void ObjectManager::Update()
{
	for each (auto obj in m_dynamic)
	{
		obj->Update();
	}
}

void ObjectManager::FixedUpdate()
{
	for each (auto obj in m_dynamic)
	{
		obj->FixedUpdate();
	}
}

void ObjectManager::OnRender()
{
	//To be added.
}

void ObjectManager::CollisionUpdate()
{
	//Consist of four steps, collision detection, then resolution.
	//Detection could be done threaded, 
	//and each object store the resulting data 
	//used for resolution.

	//Detection for moving objects.

	//Resolution will apply the changes of the detection.

	//Detection for static objects.
	//If an object is static, we will not do this step, 
	//as static vs static is not needed.


	//Resolution will apply the changes of the detection.


}
