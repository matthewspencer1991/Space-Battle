#include "PlayerInput.h"
#include "Helper.h"
#include "GameObject.h"
#include <iostream>
#include <glm\vec2.hpp>

namespace helper = MATT_SPENCER_HELPER_NAMESPACE;

PlayerInput::PlayerInput()
{
	rot_speed = 5.5f;
	speed = 10.00f;
	start_time = clock.getElapsedTime();
	bullet_state = BULLET_STATE::CIRCULAR;
}


PlayerInput::~PlayerInput()
{
}

void PlayerInput::update(GameObject& gameobject, IWorld* world)
{
	//std::cout << "X : " << gameobject.get_position().x << "Y: " << gameobject.get_position().y << std::endl;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		gameobject.set_rot_vel(-rot_speed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		gameobject.set_rot_vel(rot_speed);
	}
	else
	{
		gameobject.set_rot_vel(0.00f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		glm::vec2 forward(cos(helper::deg_to_rad(gameobject.get_rot() + GameObject::ROT_OFFSET)), sin(helper::deg_to_rad(gameobject.get_rot() + GameObject::ROT_OFFSET)));
		gameobject.set_velocity(forward * speed);
	}
	else
	{
		gameobject.set_velocity(gameobject.get_velocity() * DAMPING);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		sf::Time time_now;
		switch (bullet_state)
		{
		case BULLET_STATE::SINGLE:
			time_now = clock.getElapsedTime();
			if ((time_now.asMilliseconds() - start_time.asMilliseconds()) >= TIME_BETWEEN_SHOT)
			{
				GameObject* bullet = world->request_player_bullet();
				if (bullet != NULL)
				{
					bullet->set_position(gameobject.get_position());
					bullet->set_prev_position(gameobject.get_position());
					bullet->set_direction(glm::vec2(cos(helper::deg_to_rad(gameobject.get_rot() + GameObject::ROT_OFFSET)), sin(helper::deg_to_rad(gameobject.get_rot() + GameObject::ROT_OFFSET))));
					bullet->set_rot(gameobject.get_rot());
					bullet->set_dead(false);
				}
				start_time = time_now;
			}
			break;
		case BULLET_STATE::DOUBLE:
			time_now = clock.getElapsedTime();
			if ((time_now.asMilliseconds() - start_time.asMilliseconds()) >= TIME_BETWEEN_SHOT)
			{
				GameObject* bullet1 = world->request_player_bullet();
				if (bullet1 != NULL)
				{
					/*
						x' = x * cos(theta) - y * sin(theta)
						y' = x * sin(theta) + y * cos(theta)
					*/
					
					// Calculate right vector
					glm::vec2 right(-1.00f, 0.00f);
					float x = right.x * cos(helper::deg_to_rad(gameobject.get_rot())) - right.y * sin(helper::deg_to_rad(gameobject.get_rot()));
					float y = right.x * sin(helper::deg_to_rad(gameobject.get_rot())) + right.y * cos(helper::deg_to_rad(gameobject.get_rot()));
					right = glm::vec2(x, y);
					bullet1->set_position(gameobject.get_position() + (right * -DOUBLE_BULLET_OFFSET));
					bullet1->set_prev_position(gameobject.get_position());
					bullet1->set_direction(glm::vec2(cos(helper::deg_to_rad(gameobject.get_rot() + GameObject::ROT_OFFSET)), sin(helper::deg_to_rad(gameobject.get_rot() + GameObject::ROT_OFFSET))));
					bullet1->set_rot(gameobject.get_rot());
					bullet1->set_dead(false);
				}
				GameObject* bullet2 = world->request_player_bullet();
				if (bullet2 != NULL)
				{
					/*
					x' = x * cos(theta) - y * sin(theta)
					y' = x * sin(theta) + y * cos(theta)
					*/

					// Calculate right vector
					glm::vec2 right(-1.00f, 0.00f);
					float x = right.x * cos(helper::deg_to_rad(gameobject.get_rot())) - right.y * sin(helper::deg_to_rad(gameobject.get_rot()));
					float y = right.x * sin(helper::deg_to_rad(gameobject.get_rot())) + right.y * cos(helper::deg_to_rad(gameobject.get_rot()));
					right = glm::vec2(x, y);
					bullet2->set_position(gameobject.get_position() + right * DOUBLE_BULLET_OFFSET);
					bullet2->set_prev_position(gameobject.get_position());
					bullet2->set_direction(glm::vec2(cos(helper::deg_to_rad(gameobject.get_rot() + GameObject::ROT_OFFSET)), sin(helper::deg_to_rad(gameobject.get_rot() + GameObject::ROT_OFFSET))));
					bullet2->set_rot(gameobject.get_rot());
					bullet2->set_dead(false);
				}
				start_time = time_now;
			}
			break;
		case BULLET_STATE::CIRCULAR:
			time_now = clock.getElapsedTime();
			if ((time_now.asMilliseconds() - start_time.asMilliseconds()) >= TIME_BETWEEN_SHOT)
			{
				GameObject* bullet1 = world->request_player_bullet();
				GameObject* bullet2 = world->request_player_bullet();
				GameObject* bullet3 = world->request_player_bullet();
				GameObject* bullet4 = world->request_player_bullet();
				GameObject* bullet5 = world->request_player_bullet();
				GameObject* bullet6 = world->request_player_bullet();
				GameObject* bullet7 = world->request_player_bullet();
				GameObject* bullet8 = world->request_player_bullet();

				if (bullet1 != NULL)
				{
					bullet1->set_position(gameobject.get_position());
					bullet1->set_prev_position(gameobject.get_position());
					bullet1->set_direction(glm::vec2(0, 1));
					bullet1->set_rot(180);
				}
				if (bullet2 != NULL)
				{
					bullet2->set_position(gameobject.get_position());
					bullet2->set_prev_position(gameobject.get_position());
					bullet2->set_direction(glm::vec2(1, 0));
					bullet2->set_rot(90);
				}
				if (bullet3 != NULL)
				{
					bullet3->set_position(gameobject.get_position());
					bullet3->set_prev_position(gameobject.get_position());
					bullet3->set_direction(glm::vec2(0, -1));
					bullet3->set_rot(0);
				}
				if (bullet4 != NULL)
				{
					bullet4->set_position(gameobject.get_position());
					bullet4->set_prev_position(gameobject.get_position());
					bullet4->set_direction(glm::vec2(-1, 0));
					bullet4->set_rot(90 - 180);
				}
				if (bullet5 != NULL)
				{
					bullet5->set_position(gameobject.get_position());
					bullet5->set_prev_position(gameobject.get_position());
					bullet5->set_direction(glm::vec2(-sqrt(2) / 2, sqrt(2) / 2));
					bullet5->set_rot(225);
				}
				if (bullet6 != NULL)
				{
					bullet6->set_position(gameobject.get_position());
					bullet6->set_prev_position(gameobject.get_position());
					bullet6->set_direction(glm::vec2(-sqrt(2) / 2, -sqrt(2) / 2));
					bullet6->set_rot(135 - 180);
				}
				if (bullet7 != NULL)
				{
					bullet7->set_position(gameobject.get_position());
					bullet7->set_prev_position(gameobject.get_position());
					bullet7->set_direction(glm::vec2(sqrt(2) / 2, -sqrt(2) / 2));
					bullet7->set_rot(45);
				}
				if (bullet8 != NULL)
				{
					bullet8->set_position(gameobject.get_position());
					bullet8->set_prev_position(gameobject.get_position());
					bullet8->set_direction(glm::vec2(sqrt(2) / 2, sqrt(2) / 2));
					bullet8->set_rot(135);
				}
				start_time = time_now;
			}
			break;
		}
	}
}