#pragma once

class Object;

class Component
{
	bool mEnabled = true;
public:
	Object* mGameObject;

	virtual void Start()=0;
	virtual void Destroy()=0;
	virtual void Update(float deltaTime)=0;
	virtual void FixedUpdate(float deltaTime)=0;

	virtual void setEnable(bool e)
	{
		mEnabled = e;
	}
	virtual bool isEnabled()
	{
		return mEnabled;
	}
};