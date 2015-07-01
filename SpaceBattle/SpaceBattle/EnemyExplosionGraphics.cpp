#include "EnemyExplosionGraphics.h"
#include "Helper.h"
#include "GameObject.h"
#include <SFML\Graphics\RenderWindow.hpp>
#include <glm\vec2.hpp>

namespace helper = MATT_SPENCER_HELPER_NAMESPACE;

EnemyExplosionGraphics::EnemyExplosionGraphics()
{
}


EnemyExplosionGraphics::~EnemyExplosionGraphics()
{
}

void EnemyExplosionGraphics::draw(sf::RenderWindow& window, float through_next_frame, GameObject& gameobject, const float& rotation)
{
	// update sprite's position before drawing
	glm::vec2 pos = helper::lerp(gameobject.get_prev_position(), gameobject.get_position(), through_next_frame);
	gameobject.get_sprite().setPosition(pos.x, pos.y);

	// update sprite's rotation before drawing
	gameobject.get_sprite().setRotation(rotation);

	// draw sprite
	window.draw(gameobject.get_sprite());
}
