#pragma once

class GameObject;
class IInput;
class IGraphics;
class IAnimator;
class ICollider;


#include "IWorld.h"
#include <vector>
#include "Camera.h"

namespace sf
{
	class Texture;
}



class World1 : public IWorld
{
public:
	World1();
	~World1();
	virtual bool create();
	bool create_player_bullets();
	bool create_enemy_pods();
	void destroy_gameobjects();
	void destroy_textures();
	GameObject* get_player() const;
	std::vector<GameObject*> get_gameobjects() const;
	virtual GameObject* request_player_bullet() const;
	virtual GameObject* request_enemy_pod() const;
	virtual void input();
	virtual void update();
	virtual void draw(sf::RenderWindow& window, float through_next_frame);
	virtual bool cleanup();
private:
	IInput* player_input;
	IGraphics* player_graphics;
	IAnimator* player_animator;
	ICollider* player_collider;
	GameObject* player;

	IInput* bullet_input;
	IGraphics* bullet_graphics;
	IInput* enemy_pod_AI;
	IGraphics* enemy_pod_graphics;
	IAnimator* enemy_pod_animator;

	std::vector<IInput*> bullet_inputs_components;
	std::vector<IGraphics*> bullet_graphic_components;
	std::vector<GameObject*> gameobjects;
	std::vector<sf::Texture*> sprite_textures;
	sf::View camera;
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
	const int TEXTURE_COUNT = 3;
	const int MAX_PLAYER_BULLETS = 500;
	const int MAX_ENEMY_PODS = 10;
	glm::vec2 camera_prev_centre;
};

