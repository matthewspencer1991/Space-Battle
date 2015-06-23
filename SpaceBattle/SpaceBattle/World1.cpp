#include "World1.h"
#include <glm\vec2.hpp>
#include "GameObject.h"
#include "BulletGraphics.h"
#include "BulletInput.h"
#include "PlayerGraphics.h"
#include "PlayerInput.h"

World1::World1()
{
	player_input = NULL;
	player_graphics = NULL;
	player = NULL;
	bullet_input = NULL;
	bullet_graphics = NULL;
}


World1::~World1()
{
}

bool World1::create()
{
	// Load sprite textures
	sprite_textures.resize(2);
	sf::Texture* bullet_texture = new sf::Texture();
	bullet_texture->loadFromFile("bullet_red.png");
	bullet_texture->setSmooth(true);
	sprite_textures[0] = bullet_texture;
	sf::Texture* player_texture = new sf::Texture();
	player_texture->loadFromFile("small_ships.png");
	player_texture->setSmooth(true);
	sprite_textures[1] = player_texture;

	player_input = new PlayerInput();
	player_graphics = new PlayerGraphics();
	player = new GameObject(player_input, player_graphics, sprite_textures[1], glm::vec2(800 / 2, 600 / 2), glm::vec2(0.00f, 0.00f));
	create_player_bullets();

	return true;
}

bool World1::create_player_bullets()
{
	// Set the maximum amount of bullets that can be shown on screen at once
	player_bullets.resize(1000);
	bullet_input = new BulletInput();
	bullet_graphics = new BulletGraphics();
	
	for (unsigned int i = 0; i < player_bullets.size(); i++)
	{
		GameObject* new_bullet = new GameObject(bullet_input, bullet_graphics, sprite_textures[0], glm::vec2(0.00f, 0.00f), glm::vec2(0.00f, 0.00f));
		player_bullets[i] = new_bullet;
		// make bullets initially dead
		player_bullets[i]->set_dead(true);
	}
	return true;
}

GameObject* World1::request_player_bullet() const
{
	GameObject* bullet = NULL;
	for (unsigned int i = 0; i < player_bullets.size(); i++)
	{
		if (player_bullets[i]->get_dead())
		{
			bullet = player_bullets[i];
			bullet->set_dead(false);
			return bullet; 
		}
	}
	return bullet;
}

void World1::destroy_player_bullets()
{
	for (unsigned int i = 0; i < player_bullets.size(); i++)
	{
		if (player_bullets[i] != NULL)
			delete player_bullets[i];
	}
}

void World1::destroy_bullet_graphics()
{

}

void World1::destroy_bullet_inputs()
{

}

void World1::destroy_textures()
{
	for (unsigned int i = 0; i < sprite_textures.size(); i++)
	{
		delete sprite_textures[i];
	}
}

void World1::input()
{
	player->handle_input(this);
	for (int i = 0; i < player_bullets.size(); i++)
	{
		player_bullets[i]->handle_input(this);
	}
}

void World1::update()
{
	player->update();
	for (int i = 0; i < player_bullets.size(); i++)
	{
		player_bullets[i]->update();
	}
}

void World1::draw(sf::RenderWindow& window, float through_next_frame)
{
	player->draw(window, through_next_frame);
	for (int i = 0; i < player_bullets.size(); i++)
	{
		player_bullets[i]->draw(window, through_next_frame);
	}
}

bool World1::cleanup()
{
	delete player;
	delete player_graphics;
	delete player_input;
	destroy_player_bullets();
	destroy_textures();
	delete bullet_graphics;
	delete bullet_input;
	return true;
}
