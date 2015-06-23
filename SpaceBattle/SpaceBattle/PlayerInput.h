#pragma once
#include "IInput.h"
#include <SFML\Graphics.hpp>
#include "World1.h"
class World1;
class PlayerInput : public IInput
{
public:
	PlayerInput();
	~PlayerInput();
	virtual void update(GameObject& gameobject, IWorld* world);
private:
	float rot_speed;
	float speed;
	sf::Clock clock;
	sf::Time start_time;
	enum BULLET_STATE {SINGLE, DOUBLE, CIRCULAR};
	BULLET_STATE bullet_state;
	const int TIME_BETWEEN_SHOT = 500;
	const float DAMPING = 0.99f;
	const float DOUBLE_BULLET_OFFSET = 8.00f;
};

