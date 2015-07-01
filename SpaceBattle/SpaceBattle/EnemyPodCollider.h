#pragma once
#include "ICollider.h"
class EnemyPodCollider : public ICollider
{
public:
	EnemyPodCollider();
	~EnemyPodCollider();
	virtual void update(GameObject& gameobject, const IWorld* world);
};

