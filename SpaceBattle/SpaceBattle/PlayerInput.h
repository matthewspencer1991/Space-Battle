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
};

