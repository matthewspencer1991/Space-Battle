#include "EnemyExplosionAnimator.h"
#include "GameObject.h"


EnemyExplosionAnimator::EnemyExplosionAnimator()
{
	frame = 0;
}


EnemyExplosionAnimator::~EnemyExplosionAnimator()
{
}

void EnemyExplosionAnimator::update(GameObject& gameobject)
{
	// update source rect
	if (frame == FRAMES)
	{
		frame = 0;
		// once the animation has played once, set the explosion to dead
		gameobject.set_dead(true);
	}
	sf::IntRect updated_src_rect = gameobject.get_source_rect();
	updated_src_rect.left = frame * FRAME_WIDTH;
	gameobject.set_source_rect(updated_src_rect);
	frame++;
}
