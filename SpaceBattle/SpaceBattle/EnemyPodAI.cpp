#include "EnemyPodAI.h"
#include <glm\vec2.hpp>
#include <glm\geometric.hpp>
#include <glm\trigonometric.hpp>
#include "IWorld.h"
#include "GameObject.h"
#include <cmath>
#include <iostream>
#include "Helper.h"

namespace helper = MATT_SPENCER_HELPER_NAMESPACE;

EnemyPodAI::EnemyPodAI()
{
	state = STATE::MOVE_TO_PLAYER;
	time = clock.restart();
}


EnemyPodAI::~EnemyPodAI()
{
}

void EnemyPodAI::update(GameObject& gameobject, IWorld* world)
{
	GameObject* player = world->get_player();
	glm::vec2 dir;
	float angle = 0.00f;

	switch (state)
	{
	case STATE::MOVE_TO_PLAYER:
		dir = player->get_position() - gameobject.get_position();
		if (glm::length(dir) <= DIST_TO_CIRCLE)
		{
			state = STATE::CIRCLE_PLAYER;
		}
		gameobject.set_velocity(glm::normalize(dir) * SPEED);

		// get angle to player in radians
		angle = atan2f(dir.y, dir.x);

		angle = glm::degrees(angle) - GameObject::ROT_OFFSET;
		// set new rotation in degrees
		gameobject.set_rot(angle);
		break;
	case STATE::CIRCLE_PLAYER:
		dir = player->get_position() - gameobject.get_position();
		if (glm::length(dir) > DIST_TO_CIRCLE)
		{
			state = STATE::MOVE_TO_PLAYER;
		}
		else
		{
			time = clock.getElapsedTime();
			dir = player->get_position() - gameobject.get_position();

			/*
				x' = x * cos(theta) - y * sin(theta)
				y' = x * sin(theta) + y * cos(theta)
			*/

			// Calculate right vector
			glm::vec2 right(1.00f, 0.00f);
			float x = right.x * cos(helper::deg_to_rad(gameobject.get_rot())) - right.y * sin(helper::deg_to_rad(gameobject.get_rot()));
			float y = right.x * sin(helper::deg_to_rad(gameobject.get_rot())) + right.y * cos(helper::deg_to_rad(gameobject.get_rot()));
			right = glm::vec2(x, y);

			gameobject.set_velocity(glm::normalize(right) * (SPEED / 3));

			// get angle to player in radians
			angle = atan2f(dir.y, dir.x);

			angle = glm::degrees(angle) - GameObject::ROT_OFFSET;
			// set new rotation in degrees
			gameobject.set_rot(angle);
		}
		break;
	}
}
