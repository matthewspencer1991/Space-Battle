#pragma once
#include "IAnimator.h"
class EnemyPodAnimator : public IAnimator
{
public:
	EnemyPodAnimator();
	~EnemyPodAnimator();
	void update(GameObject& gameobject);
private:
	const int FRAMES = 8;
	const int FRAME_WIDTH = 64;
	int frame = 1;
};

