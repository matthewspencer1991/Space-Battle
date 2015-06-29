#pragma once

class GameObject;

namespace sf
{
	class Graphics;
	class RenderWindow;
}

class IWorld
{
public:
	virtual ~IWorld() {}
	virtual GameObject* request_player_bullet() const = 0;
	virtual GameObject* request_enemy_pod() const = 0;
	virtual GameObject* get_player() const = 0;
	virtual bool create() = 0;
	virtual void input() = 0;
	virtual void update() = 0;
	virtual void draw(sf::RenderWindow& window, float through_next_frame) = 0;
	virtual bool cleanup() = 0;
};