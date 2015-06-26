#pragma once
#include "IInput.h"
class EnemyPodAI :
	public IInput
{
public:
	EnemyPodAI();
	~EnemyPodAI();
	void update(GameObject& gameobject, IWorld* world);
};

