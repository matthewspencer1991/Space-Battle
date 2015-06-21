#include "GameObject.h"
#include "IInput.h"
#include "IGraphics.h"

GameObject::GameObject(IInput* _input, IGraphics* _graphics, sf::Texture* sprite_texture, const glm::vec2& _position, const glm::vec2& _velocity)
	: prev_position(0.00f, 0.00f), position(_position.x, _position.y), velocity(_velocity.x, _velocity.y), direction(0.00f, 0.00f)
{
	input = _input;
	graphics = _graphics;
	texture = sprite_texture;
	sprite.setTexture(*texture);
	sprite.setOrigin(texture->getSize().x / 2, texture->getSize().y / 2);
	rotation = 0.00f;
	rotation_vel = 0.00f;
	dead = false;
}

GameObject::~GameObject()
{
}

bool GameObject::get_dead() const
{
	return dead;
}

void GameObject::set_dead(const bool new_dead_state)
{
	dead = new_dead_state;
}

sf::Sprite& GameObject::get_sprite() 
{
	return sprite;
}

glm::vec2 GameObject::get_prev_position() const
{
	return prev_position;
}

void GameObject::set_prev_position(const glm::vec2& new_prev_position)
{
	prev_position = new_prev_position;
}

glm::vec2 GameObject::get_position() const
{
	return position;
}

void GameObject::set_position(const glm::vec2& new_position)
{
	position = new_position;
}

glm::vec2 GameObject::get_velocity() const
{
	return velocity;
}

void GameObject::set_velocity(const glm::vec2& new_velocity)
{
	velocity = new_velocity;
}

glm::vec2 GameObject::get_direction() const
{
	return direction;
}

void GameObject::set_direction(const glm::vec2& new_direction)
{
	direction = new_direction;
}

float GameObject::get_rot() const
{
	return rotation;
}

void GameObject::set_rot(const float new_rot)
{
	rotation = new_rot;
}

float GameObject::get_rot_vel() const
{
	return rotation_vel;
}

void GameObject::set_prev_rot(const float new_prev_rot)
{
	prev_rotation = new_prev_rot;
}

float GameObject::get_prev_rot() const
{
	return prev_rotation;
}

void GameObject::set_rot_vel(const float new_rot_vel)
{
	rotation_vel = new_rot_vel;
}

void GameObject::handle_input(IWorld* world)
{
	if (input != NULL && !dead)
	{
		input->update(*this, world);
	}
}

void GameObject::update()
{
	// update position and rotation
	if (!dead)
	{
		// store previous position for interpolation
		prev_position = position;
		position = position + velocity;
		prev_rotation = rotation;
		rotation += rotation_vel;
	}
}

void GameObject::draw(sf::RenderWindow& window, float through_next_frame)
{
	if (graphics != NULL && !dead)
	{
		graphics->draw(window, through_next_frame, *this, rotation);
	}
}
