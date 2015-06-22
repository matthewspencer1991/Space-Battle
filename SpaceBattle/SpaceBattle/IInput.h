#pragma once

class IWorld;
class GameObject;

class IInput
{
public:
	virtual ~IInput() {}
	virtual void update(GameObject& gameobject, IWorld* world) = 0;
};