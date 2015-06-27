#include "EnemyPodAI.h"
#include <glm\vec2.hpp>
#include <glm\geometric.hpp>
#include <glm\trigonometric.hpp>
#include "IWorld.h"
#include "GameObject.h"
#include <cmath>

EnemyPodAI::EnemyPodAI()
{
}


EnemyPodAI::~EnemyPodAI()
{
}

void EnemyPodAI::update(GameObject& gameobject, IWorld* world)
{
	// Rotate towards player

	// Get direction vector of player
	GameObject* player = world->get_player();
	glm::vec2 dir = player->get_position() - gameobject.get_position();
	// normalise direction
	dir = glm::normalize(dir);

	// get angle to player in radians
	float angle = atan2f(dir.y, dir.x);

	angle = glm::degrees(angle) - GameObject::ROT_OFFSET;
	// set new rotation in degrees
	gameobject.set_rot(angle);
}
