#pragma once
#include <list>
class Object;
class ObjectManager
{
	std::list<Object*> m_allObjects;
	//Does not call update on static objects.
	std::list<Object*> m_static;
	//Calls update on nonstatic objects.
	std::list<Object*> m_dynamic;
	std::list<Object*> m_Collidable;

public:
	ObjectManager();
	~ObjectManager();

	void RemoveObject(Object* o);
	void AddObject(Object* o);

	void Update();
	void FixedUpdate();
	void OnRender();
	void CollisionUpdate();
};
