#include "EnemyPodCollider.h"
#include "GameObject.h"
#include "IWorld.h"
#include <iostream>

EnemyPodCollider::EnemyPodCollider()
{
}


EnemyPodCollider::~EnemyPodCollider()
{
}

void EnemyPodCollider::update(GameObject& gameobject, const IWorld* world)
{
	std::vector<GameObject*> other_gameobjects = world->get_gameobjects();
	for (GameObject* other : other_gameobjects)
	{
		if (!other->get_dead() && other->get_tag() == "player_bullet" && gameobject.get_sprite().getGlobalBounds().intersects(other->get_sprite().getGlobalBounds()))
		{
			// Handle collision
			gameobject.set_dead(true);
			std::cout << "Collision enemy pod!" << "\n";
			// Spawn explosion
			GameObject* enemy_pod_explos = world->request_enemy_pod_explosion();
			if (enemy_pod_explos != NULL)
			{
				enemy_pod_explos->set_position(gameobject.get_position());
				enemy_pod_explos->set_dead(false);
			}
		}
	}
}
