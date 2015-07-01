#pragma once
#include "IAnimator.h"

class GameObject;

class PlayerAnimator : public IAnimator
{
public:
	PlayerAnimator();
	~PlayerAnimator();
	void update(GameObject& gameobject);
private:
	const int FRAMES = 5;
	const int FRAME_WIDTH = 64;
	int frame;
};

