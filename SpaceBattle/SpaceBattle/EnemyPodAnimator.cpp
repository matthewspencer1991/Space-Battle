#include "EnemyPodAnimator.h"
#include "GameObject.h"

EnemyPodAnimator::EnemyPodAnimator()
{
}


EnemyPodAnimator::~EnemyPodAnimator()
{
}

void EnemyPodAnimator::update(GameObject& gameobject)
{
	// update source rect
	if (frame == FRAMES)
	{
		frame = 0;
	}
	sf::IntRect updated_src_rect = gameobject.get_source_rect();
	updated_src_rect.left = frame * FRAME_WIDTH;
	gameobject.set_source_rect(updated_src_rect);
	frame++;
}
