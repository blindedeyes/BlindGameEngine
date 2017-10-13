#pragma once
#include <vector>
#include "Component.h"

class ObjectManager;
class MeshRenderer;
//class Collider;
class Object
{
	bool m_Enabled = true;
	bool m_Static = false;
	std::vector<Component*> m_Components;
	ObjectManager* m_ObjManager;
	//std::vector<Collider*> m_Colliders;
public:
	MeshRenderer* m_MeshRenderer=0;
	Object(bool isStatic)
	{
		m_Static = isStatic;
	}
	~Object()
	{
		for (unsigned int i = 0; i < m_Components.size(); ++i)
		{
			delete m_Components[i];
		}
	}

	virtual void Update();
	virtual void Start();
	virtual void CollisionUpdate();
	virtual void FixedUpdate();

	virtual void SetRenderer(MeshRenderer* rend)
	{
		m_MeshRenderer = rend;
		//m_ObjManager->AddRenderable(rend);
	}

	virtual void setEnabled(bool e)
	{
		m_Enabled = e;
	}

	virtual bool isEnabled()
	{
		return m_Enabled;
	}
	virtual bool isStatic()
	{
		return m_Static;
	}

	virtual void AddComponent(Component* c)
	{
		m_Components.push_back(c);
		c->m_GameObject = this;
	}
	template <typename type>
	type* GetComponent()
	{
		type* res = nullptr;
		for (unsigned int i = 0; i < m_Components.size(); ++i)
		{
			res = dynamic_cast<type*>(m_Components[i]);
			if (res)
			{
				break;
			}
		}
		//one exit point
		return res;
	}
};

