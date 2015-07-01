#pragma once
class GameObject;
#include "IAnimator.h"
class EnemyExplosionAnimator : public IAnimator
{
public:
	EnemyExplosionAnimator();
	~EnemyExplosionAnimator();
	virtual void update(GameObject& gameobject);
private:
	const int FRAMES = 17;
	const int FRAME_WIDTH = 64;
	int frame;
};

