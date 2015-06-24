#include "BulletInput.h"
#include "GameObject.h"

BulletInput::BulletInput() 
{
	speed = 15.50f;
}

BulletInput::~BulletInput()
{
}

void BulletInput::update(GameObject& gameobject, IWorld* world)
{
	gameobject.set_velocity(gameobject.get_direction() * speed);
}
