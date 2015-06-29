#pragma once
#include "ICollider.h"

class PlayerCollider : public ICollider
{
public:
	PlayerCollider();
	virtual ~PlayerCollider();
	virtual void update(GameObject& gameobject, std::vector<GameObject*> other_gameobjects);
};

