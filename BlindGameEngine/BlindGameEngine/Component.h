#pragma once

class Object;

class Component
{
	bool m_Enabled = true;
public:
	Object* m_GameObject;

	Component() {};
	~Component() {};
	virtual void Start()=0;
	virtual void Destroy()=0;
	virtual void Update()=0;
	virtual void FixedUpdate()=0;

	virtual void setEnable(bool e)
	{
		m_Enabled = e;
	}
	virtual bool isEnabled()
	{
		return m_Enabled;
	}
};