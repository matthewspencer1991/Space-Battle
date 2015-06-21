#pragma once

class GameObject;
class IInput;
class IGraphics;


#include "IWorld.h"
#include <vector>

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
	GameObject* player;
	IInput* bullet_input;
	IGraphics* bullet_graphics;
	std::vector<IInput*> bullet_inputs_components;
	std::vector<IGraphics*> bullet_graphic_components;
	std::vector<GameObject*> player_bullets;
	std::vector<sf::Texture*> sprite_textures;
};

