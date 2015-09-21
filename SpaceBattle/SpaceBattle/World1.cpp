#include "World1.h"
#include <glm\vec2.hpp>
#include "GameObject.h"
#include "BulletGraphics.h"
#include "BulletInput.h"
#include "PlayerGraphics.h"
#include "PlayerInput.h"
#include "PlayerCollider.h"
#include "Helper.h"
#include "PlayerAnimator.h"
#include "EnemyPodAI.h"
#include "EnemyPodGraphics.h"
#include "EnemyPodAnimator.h"
#include "EnemyPodCollider.h"
#include "EnemyExplosionGraphics.h"
#include "EnemyExplosionAnimator.h"
#include <cstdlib>

namespace helper = MATT_SPENCER_HELPER_NAMESPACE;

World1::World1() 
{
	player_input = NULL;
	player_graphics = NULL;
	player_animator = NULL;
	player_collider = NULL; 
	player = NULL;
	bullet_input = NULL;
	bullet_graphics = NULL;
	enemy_pod_AI = NULL;
	enemy_pod_graphics = NULL;
	enemy_pod_animator = NULL;
	enemy_pod_collider = NULL;
	enemy_explosion_graphics = NULL;
	enemy_explosion_animator = NULL;

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
	player_collider = new PlayerCollider();
	const int PLAYER_WIDTH = 64;
	const int PLAYER_HEIGHT = 64;
	player = new GameObject(player_input, player_graphics, player_animator, player_collider, sprite_textures[1], glm::vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), glm::vec2(0.00f, 0.00f), sf::IntRect(0, 0, PLAYER_WIDTH, PLAYER_HEIGHT));
	player->set_tag("player");
	create_player_bullets();
	create_enemy_pods();

	// create enemy explosions
	enemy_explosion_graphics = new EnemyExplosionGraphics();
	enemy_explosion_animator = new EnemyExplosionAnimator();
	sf::Texture* enemy_explosion_texture = new sf::Texture();
	enemy_explosion_texture->loadFromFile("Sprites\\explosion64x64.png");
	sprite_textures[3] = enemy_explosion_texture;
	const int EXPLOSION_WIDTH = 64;
	const int EXPLOSION_HEIGHT = 64;

	// create the same amount of enemy explosions as pods
	for (int i = 0; i < MAX_ENEMY_PODS; i++)
	{
		GameObject* enemy_pod_explosion = new GameObject(NULL, enemy_explosion_graphics, enemy_explosion_animator, NULL, sprite_textures[3], glm::vec2(0.00f, 0.00f), glm::vec2(0.00f, 0.00f), sf::IntRect(0, 0, EXPLOSION_WIDTH, EXPLOSION_HEIGHT));
		enemy_pod_explosion->set_tag("enemy_pod_explosion");
		enemy_pod_explosion->set_dead(true);
		gameobjects.push_back(enemy_pod_explosion);
	}

	// create intial enemy pods
	for (int i = 0; i < MAX_ENEMY_PODS; i++)
	{
		GameObject* new_pod = request_enemy_pod();
		if (new_pod != NULL)
		{
			int rand_x = rand() % SCREEN_WIDTH + 1;
			int rand_y = rand() % SCREEN_HEIGHT + 1;
			new_pod->set_position(glm::vec2(rand_x, rand_y));
		}
	}

	return true;
}

bool World1::create_player_bullets() 
{
	// Set the maximum amount of bullets that can be shown on screen at once
	bullet_input = new BulletInput();
	bullet_graphics = new BulletGraphics();
	
	for (int i = 0; i < MAX_PLAYER_BULLETS; i++)
	{
		const int BULLET_WIDTH = 32;
		const int BULLET_HEIGHT = 32;
		GameObject* new_bullet = new GameObject(bullet_input, bullet_graphics, NULL, NULL, sprite_textures[0], glm::vec2(0.00f, 0.00f), glm::vec2(0.00f, 0.00f), sf::IntRect(0, 0, BULLET_WIDTH, BULLET_HEIGHT));
		// make bullets initially dead
		new_bullet->set_dead(true);
		new_bullet->set_tag("player_bullet");
		gameobjects.push_back(new_bullet);
	}
	return true;
}

bool World1::create_enemy_pods() 
{
	// set the maximum amount of enemy pods that can be on screen at once

	enemy_pod_AI = new EnemyPodAI();
	enemy_pod_graphics = new EnemyPodGraphics();
	enemy_pod_animator = new EnemyPodAnimator();
	enemy_pod_collider = new EnemyPodCollider();
	const int ENEMY_POD_WIDTH = 64;
	const int ENEMY_POD_HEIGHT = 64;

	for (int i = 0; i < MAX_ENEMY_PODS; i++)
	{
		GameObject* new_enemy_pod = new GameObject(enemy_pod_AI, enemy_pod_graphics, enemy_pod_animator, enemy_pod_collider, sprite_textures[2], glm::vec2(0, 0), glm::vec2(0.00f, 0.00f), sf::IntRect(0, 0, ENEMY_POD_WIDTH, ENEMY_POD_HEIGHT));
		// make enemy pod initially dead
		new_enemy_pod->set_dead(true);
		new_enemy_pod->set_tag("enemy_pod");
		gameobjects.push_back(new_enemy_pod);
	}
	
	return true;
}

GameObject* World1::request_player_bullet() const
{
	GameObject* bullet = NULL;
	for (unsigned int i = 0; i < gameobjects.size(); i++)
	{
		if (gameobjects[i]->get_tag() == "player_bullet" && gameobjects[i]->get_dead())
		{
			bullet = gameobjects[i];
			bullet->set_dead(false);
			return bullet; 
		}
	}
	return bullet;
}

GameObject* World1::request_enemy_pod() const
{
	GameObject* enemy_pod = NULL;
	for (GameObject* gameobject : gameobjects)
	{
		if (gameobject->get_tag() == "enemy_pod" && gameobject->get_dead())
		{
			enemy_pod = gameobject;
			enemy_pod->set_dead(false);
			return enemy_pod;
		}
	}
	return enemy_pod;

}

GameObject* World1::request_enemy_pod_explosion() const
{
	GameObject* enemy_pod_explos = NULL;
	for (GameObject* gameobject : gameobjects)
	{
		if (gameobject->get_tag() == "enemy_pod_explosion" && gameobject->get_dead())
		{
			enemy_pod_explos = gameobject;
			enemy_pod_explos->set_dead(false);
			return enemy_pod_explos;
		}
	}
	return enemy_pod_explos;
}

void World1::destroy_gameobjects()
{
	for (int i = 0; i < gameobjects.size(); i++)
	{
		if (gameobjects[i] != NULL)
			delete gameobjects[i];
	}
}

void World1::destroy_textures()
{
	for (unsigned int i = 0; i < sprite_textures.size(); i++)
	{
		delete sprite_textures[i];
	}
}

GameObject* World1::get_player() const
{
	return player;
}

const std::vector<GameObject*>& World1::get_gameobjects() const
{
	return gameobjects;
}

void World1::input()
{
	player->handle_input(this);
	for (int i = 0; i < gameobjects.size(); i++)
	{
		gameobjects[i]->handle_input(this);
	}
}

void World1::update()
{
	player->update(this);
	for (int i = 0; i < gameobjects.size(); i++)
	{
		gameobjects[i]->update(this);
	}
}

void World1::draw(sf::RenderWindow& window, float through_next_frame)
{
	// Draw game stuff, that depends on view
	// set camera centre to interpolated position
	glm::vec2 lerped_cam = helper::lerp(player->get_prev_position(), player->get_position(), through_next_frame);
	camera.setCenter(sf::Vector2f(lerped_cam.x, lerped_cam.y));
	window.setView(camera);

	for (GameObject* gameobject : gameobjects)
		gameobject->draw(window, through_next_frame);

	player->draw(window, through_next_frame);

	// Draw UI elements that don't depend on the vew
	window.setView(window.getDefaultView());
}

bool World1::cleanup()
{
	delete player;
	delete player_animator;
	delete player_graphics;
	delete player_input;
	destroy_gameobjects();
	if (enemy_pod_animator != NULL)
		delete enemy_pod_animator;
	if (enemy_pod_graphics != NULL)
		delete enemy_pod_graphics;
	if (enemy_pod_AI != NULL)
		delete enemy_pod_AI;
	if (enemy_pod_collider != NULL)
		delete enemy_pod_collider;
	if (enemy_explosion_graphics != NULL)
		delete enemy_explosion_graphics;
	if (enemy_explosion_animator != NULL)
		delete enemy_explosion_animator;
	delete bullet_graphics;
	delete bullet_input;
	destroy_textures();
	return true;
}
