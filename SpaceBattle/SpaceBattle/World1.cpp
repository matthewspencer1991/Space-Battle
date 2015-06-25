#include "World1.h"
#include <glm\vec2.hpp>
#include "GameObject.h"
#include "BulletGraphics.h"
#include "BulletInput.h"
#include "PlayerGraphics.h"
#include "PlayerInput.h"
#include "Helper.h"

namespace helper = MATT_SPENCER_HELPER_NAMESPACE;

World1::World1() 
{
	player_input = NULL;
	player_graphics = NULL;
	player = NULL;
	bullet_input = NULL;
	bullet_graphics = NULL;

	camera.reset(sf::FloatRect(0, 0, 800, 600));
	camera.setCenter(sf::Vector2f(400, 300));
	camera_prev_centre = glm::vec2(camera.getCenter().x, camera.getCenter().y);
}


World1::~World1()
{
}

bool World1::create()
{
	// Load sprite textures
	sprite_textures.resize(TEXTURE_COUNT);
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
	player = new GameObject(player_input, player_graphics, sprite_textures[1], glm::vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), glm::vec2(0.00f, 0.00f));
	create_player_bullets();

	return true;
}

bool World1::create_player_bullets()
{
	// Set the maximum amount of bullets that can be shown on screen at once
	player_bullets.resize(MAX_PLAYER_BULLETS);
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

	// set camera to new position
	//camera.setCenter(sf::Vector2f(player->get_position().x, player->get_position().y));
}

void World1::draw(sf::RenderWindow& window, float through_next_frame)
{
	// Draw game stuff, that depends on view
	// set camera centre to interpolated position
	glm::vec2 lerped_cam = helper::lerp(player->get_prev_position(), player->get_position(), through_next_frame);
	camera.setCenter(sf::Vector2f(lerped_cam.x, lerped_cam.y));
	window.setView(camera);
	player->draw(window, through_next_frame);
	// camera debug -- remove
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(50, 50));
	rect.setFillColor(sf::Color::Green);
	rect.setPosition(sf::Vector2f(0, 0));
	window.draw(rect);
	// camera debug -- remove
	for (int i = 0; i < player_bullets.size(); i++)
	{
		player_bullets[i]->draw(window, through_next_frame);
	}
	// Draw UI elements that don't depend on the vew
	window.setView(window.getDefaultView());
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
