#pragma once

class GameObject; 
class IWorld;

class ICollider
{
public:
	virtual ~ICollider() {}
	virtual void update(GameObject& gameobject, const IWorld* world) = 0;
};