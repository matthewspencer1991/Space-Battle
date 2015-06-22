#pragma once

#include "IGraphics.h"

class BulletGraphics : public IGraphics
{
public:
	BulletGraphics();
	~BulletGraphics();
	virtual void draw(sf::RenderWindow& window, float through_next_frame, GameObject& gameobject, const float& rotation);
private:

};

