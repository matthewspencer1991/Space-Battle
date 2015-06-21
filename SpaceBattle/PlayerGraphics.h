#pragma once

#include "IGraphics.h"

class PlayerGraphics : public IGraphics
{
public:
	PlayerGraphics();
	~PlayerGraphics();
	virtual void draw(sf::RenderWindow& window, float through_next_frame, GameObject& gameobject, const float& rotation);
private:

};

