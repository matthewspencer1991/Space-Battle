#pragma once
#include "IInput.h"
#include <SFML\Graphics.hpp>
class EnemyPodAI : public IInput
{
public:
	EnemyPodAI();
	~EnemyPodAI();
	void update(GameObject& gameobject, IWorld* world);
private:
	enum STATE { MOVE_TO_PLAYER, CIRCLE_PLAYER };
	STATE state;
	const float SPEED = 3;
	const float DIST_TO_CIRCLE = 200;
	const float RADIUS = 100;
	sf::Clock clock;
	sf::Time time;
};

