#include "PlayerAnimator.h"
#include "GameObject.h"

PlayerAnimator::PlayerAnimator()
{
	frame = 0;
}


PlayerAnimator::~PlayerAnimator()
{
}

void PlayerAnimator::update(GameObject& gameobject)
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
