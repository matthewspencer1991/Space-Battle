#pragma once

class GameObject;

#include <SFML\Graphics.hpp>


class IGraphics
{
public:
	virtual ~IGraphics() {}
	virtual void draw(sf::RenderWindow& window, float through_next_frame, GameObject& gameobject, const float& rotation) = 0;
};