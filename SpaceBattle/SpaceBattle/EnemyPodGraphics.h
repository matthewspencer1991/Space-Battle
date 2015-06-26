#pragma once

#include "IGraphics.h"
class EnemyPodGraphics : public IGraphics
{
public:
	EnemyPodGraphics();
	~EnemyPodGraphics();
	void draw(sf::RenderWindow& window, float through_next_frame, GameObject& gameobject, const float& rotation);
};

