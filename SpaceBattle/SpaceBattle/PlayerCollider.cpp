#include "PlayerCollider.h"

#include "GameObject.h"

PlayerCollider::PlayerCollider()
{
}


PlayerCollider::~PlayerCollider()
{
}

void PlayerCollider::update(GameObject& gameobject, std::vector<GameObject*> other_gameobjects)
{
	for (GameObject* other : other_gameobjects)
	{
		if (gameobject.get_tag() == "enemy_pod" && gameobject.get_sprite().getLocalBounds().intersects(other->get_sprite().getLocalBounds()))
		{
			// Handle collision
			gameobject.set_dead(true);
		}
	}
}
