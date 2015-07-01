#pragma once
#include "IGraphics.h"
class EnemyExplosionGraphics : public IGraphics
{
public:
	EnemyExplosionGraphics();
	~EnemyExplosionGraphics();
	virtual void draw(sf::RenderWindow& window, float through_next_frame, GameObject& gameobject, const float& rotation);
};

