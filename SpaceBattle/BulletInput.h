#pragma once

class GameObject;

#include "IInput.h"

class BulletInput : public IInput
{
public:
	BulletInput();
	~BulletInput();
	virtual void update(GameObject& gameobject, IWorld* world);
private:
	float speed;
};

