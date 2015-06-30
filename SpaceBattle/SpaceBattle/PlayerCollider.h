#pragma once
#include "ICollider.h"

class PlayerCollider : public ICollider
{
public:
	PlayerCollider();
	virtual ~PlayerCollider();
	virtual void update(GameObject& gameobject, const IWorld* world);
};

