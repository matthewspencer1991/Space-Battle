#pragma once

class IInput;
class IGraphics;
class IWorld;

#include <SFML\Graphics.hpp>
#include <glm\vec2.hpp>

class GameObject
{
public:
	GameObject(IInput* _input, IGraphics* _graphics, sf::Texture* sprite_texture, const glm::vec2& _position, const glm::vec2& _velocity);
	~GameObject();
	bool get_dead() const;
	void set_dead(const bool new_dead_state);
	sf::Sprite& get_sprite();
	glm::vec2 get_prev_position() const;
	void set_prev_position(const glm::vec2& new_prev_position);
	glm::vec2 get_position() const;
	void set_position(const glm::vec2& new_position);
	glm::vec2 get_velocity() const;
	void set_velocity(const glm::vec2& new_velocity);
	glm::vec2 get_direction() const;
	void set_direction(const glm::vec2& new_direction);
	float get_rot() const;
	void set_rot(const float new_rot);
	float get_prev_rot() const;
	void set_prev_rot(const float new_prev_rot);
	float get_rot_vel() const;
	void set_rot_vel(const float new_rot_vel);
	void handle_input(IWorld* world);
	void update();
	void draw(sf::RenderWindow& window, float through_next_frame);
private:
	IInput* input;
	IGraphics* graphics;
	sf::Texture* texture;
	sf::Sprite sprite;
	glm::vec2 prev_position;
	glm::vec2 position;
	glm::vec2 velocity;
	glm::vec2 direction;
	float rotation;
	float prev_rotation;
	float rotation_vel;
	bool dead;
};

