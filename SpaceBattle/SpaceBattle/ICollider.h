#pragma once

class GameObject; 

#include <vector>

class ICollider
{
public:
	virtual ~ICollider() {}
	virtual void update(GameObject& gameobject, std::vector<GameObject*> other_gameobjects) = 0;
};