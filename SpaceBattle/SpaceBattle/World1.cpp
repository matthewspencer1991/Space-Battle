#include "World1.h"
#include <glm\vec2.hpp>
#include "GameObject.h"
#include "BulletGraphics.h"
#include "BulletInput.h"
#include "PlayerGraphics.h"
#include "PlayerInput.h"
#include "Helper.h"
#include "PlayerAnimator.h"
#include "EnemyPodAI.h"
#include "EnemyPodGraphics.h"
#include "EnemyPodAnimator.h"

namespace helper = MATT_SPENCER_HELPER_NAMESPACE;

World1::World1() 
{
	player_input = NULL;
	player_graphics = NULL;
	player = NULL;
	bullet_input = NULL;
	bullet_graphics = NULL;
	enemy_pod_AI = NULL;
	enemy_pod_graphics = NULL;
	enemy_pod_animator = NULL;

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
	bullet_texture->loadFromFile("Sprites\\bullet32x32.png");
	bullet_texture->setSmooth(true);
	sprite_textures[0] = bullet_texture;
	sf::Texture* player_texture = new sf::Texture();
	player_texture->loadFromFile("Sprites\\small_ship_blue_spritesheet64x64.png");
	player_texture->setSmooth(true);
	sprite_textures[1] = player_texture;
	sf::Texture* enemy_pod_texture = new sf::Texture();
	enemy_pod_texture->loadFromFile("Sprites\\enemy_pod_spritesheet64x64.png");
	sprite_textures[2] = enemy_pod_texture;

	player_input = new PlayerInput();
	player_graphics = new PlayerGraphics();
	player_animator = new PlayerAnimator();
	const int PLAYER_WIDTH = 64;
	const int PLAYER_HEIGHT = 64;
	player = new GameObject(player_input, player_graphics, player_animator, sprite_textures[1], glm::vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), glm::vec2(0.00f, 0.00f), sf::IntRect(0, 0, PLAYER_WIDTH, PLAYER_HEIGHT));
	create_player_bullets();

	enemy_pod_AI = new EnemyPodAI();
	enemy_pod_graphics = new EnemyPodGraphics();
	enemy_pod_animator = new EnemyPodAnimator();
	const int ENEMY_POD_WIDTH = 64;
	const int ENEMY_POD_HEIGHT = 64;
	enemy_pod = new GameObject(enemy_pod_AI, enemy_pod_graphics, enemy_pod_animator, sprite_textures[2], glm::vec2(SCREEN_WIDTH / 2, 64.00f), glm::vec2(0.00f, 0.00f), sf::IntRect(0, 0, ENEMY_POD_WIDTH, ENEMY_POD_HEIGHT));

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
		const int BULLET_WIDTH = 32;
		const int BULLET_HEIGHT = 32;
		GameObject* new_bullet = new GameObject(bullet_input, bullet_graphics, NULL, sprite_textures[0], glm::vec2(0.00f, 0.00f), glm::vec2(0.00f, 0.00f), sf::IntRect(0, 0, BULLET_WIDTH, BULLET_HEIGHT));
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
	enemy_pod->handle_input(this);
}

void World1::update()
{
	player->update();
	for (int i = 0; i < player_bullets.size(); i++)
	{
		player_bullets[i]->update();
	}
	enemy_pod->update();
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
	for (int i = 0; i < player_bullets.size(); i++)
	{
		player_bullets[i]->draw(window, through_next_frame);
	}
	enemy_pod->draw(window, through_next_frame);
	// Draw UI elements that don't depend on the vew
	window.setView(window.getDefaultView());
}

bool World1::cleanup()
{
	delete player;
	delete player_animator;
	delete player_graphics;
	delete player_input;
	destroy_player_bullets();
	delete enemy_pod;
	delete enemy_pod_animator;
	delete enemy_pod_graphics;
	delete enemy_pod_AI;
	delete bullet_graphics;
	delete bullet_input;
	destroy_textures();
	return true;
}
