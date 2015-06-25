#pragma once

class GameObject; 

class IAnimator
{
public:
	virtual ~IAnimator() {}
	virtual void update(GameObject& gameobject) = 0;
};