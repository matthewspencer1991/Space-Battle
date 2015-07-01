#include "PlayerCollider.h"
#include "GameObject.h"
#include "IWorld.h"
#include <iostream>

PlayerCollider::PlayerCollider()
{
}


PlayerCollider::~PlayerCollider()
{
}

void PlayerCollider::update(GameObject& gameobject, const IWorld* world)
{
	std::vector<GameObject*> other_gameobjects = world->get_gameobjects();
	for (GameObject* other : other_gameobjects)
	{
		if (!other->get_dead() && other->get_tag() == "enemy_pod" && gameobject.get_sprite().getGlobalBounds().intersects(other->get_sprite().getGlobalBounds()))
		{
			// Handle collision
			std::cout << "Collision" << "\n";
			//gameobject.set_dead(true);
		}
	}
}
