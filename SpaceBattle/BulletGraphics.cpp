#include "BulletGraphics.h"
#include "Helper.h"
#include "SFML\Graphics\RenderWindow.hpp"
#include "GameObject.h"
namespace helper = MATT_SPENCER_HELPER_NAMESPACE;

BulletGraphics::BulletGraphics()
{

}


BulletGraphics::~BulletGraphics()
{
}

void BulletGraphics::draw(sf::RenderWindow& window, float through_next_frame, GameObject& gameobject, const float& rotation)
{
	// update sprite's position before drawing
	glm::vec2 pos = helper::lerp(gameobject.get_prev_position(), gameobject.get_position(), through_next_frame);
	gameobject.get_sprite().setPosition(pos.x, pos.y);

	// update sprite's rotation before drawing
	gameobject.get_sprite().setRotation(rotation);

	// draw sprite
	window.draw(gameobject.get_sprite());
}
