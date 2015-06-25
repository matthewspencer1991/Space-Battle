#pragma once

class GameObject;
class IInput;
class IGraphics;
class IAnimator;


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
	void destroy_player_bullets();
	void destroy_bullet_graphics();
	void destroy_bullet_inputs();
	void destroy_textures();
	virtual GameObject* request_player_bullet() const;
	virtual void input();
	virtual void update();
	virtual void draw(sf::RenderWindow& window, float through_next_frame);
	virtual bool cleanup();
private:
	IInput* player_input;
	IGraphics* player_graphics;
	IAnimator* player_animator;
	GameObject* player;
	IInput* bullet_input;
	IGraphics* bullet_graphics;
	std::vector<IInput*> bullet_inputs_components;
	std::vector<IGraphics*> bullet_graphic_components;
	std::vector<GameObject*> player_bullets;
	std::vector<sf::Texture*> sprite_textures;
	sf::View camera;
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
	const int TEXTURE_COUNT = 2;
	const int MAX_PLAYER_BULLETS = 500;
	glm::vec2 camera_prev_centre;
};

