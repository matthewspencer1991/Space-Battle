#pragma once

class IInput;
class IGraphics;
class IWorld;
class IAnimator;
class ICollider;

#include <SFML\Graphics.hpp>
#include <glm\vec2.hpp>

class GameObject
{
public:
	GameObject(IInput* _input, IGraphics* _graphics, IAnimator* _animator, ICollider* _collider, sf::Texture* sprite_texture, const glm::vec2& _position, const glm::vec2& _velocity, const sf::IntRect& _source_rect);
	~GameObject();
	sf::Sprite& get_sprite();
	glm::vec2 get_prev_position() const;
	void set_prev_position(const glm::vec2& new_prev_position);
	glm::vec2 get_position() const;
	void set_position(const glm::vec2& new_position);
	glm::vec2 get_velocity() const;
	void set_velocity(const glm::vec2& new_velocity);
	glm::vec2 get_direction() const;
	void set_direction(const glm::vec2& new_direction);
	sf::IntRect get_source_rect() const;
	void set_source_rect(const sf::IntRect& new_source_rect);
	float get_rot() const;
	void set_rot(const float new_rot);
	float get_prev_rot() const;
	void set_prev_rot(const float new_prev_rot);
	float get_rot_vel() const;
	void set_rot_vel(const float new_rot_vel);
	bool get_dead() const;
	void set_dead(const bool new_dead_state);
	std::string get_tag() const;
	void set_tag(const std::string& new_tag);
	void handle_input(IWorld* world);
	void update(const IWorld* world);
	void draw(sf::RenderWindow& window, float through_next_frame);

	static const int ROT_OFFSET = -90;
private:
	IInput* input;
	IGraphics* graphics;
	IAnimator* animator;
	ICollider* collider;
	sf::Texture* texture;
	sf::Sprite sprite;
	glm::vec2 prev_position;
	glm::vec2 position;
	glm::vec2 velocity;
	glm::vec2 direction;
	sf::IntRect source_rect;
	float rotation;
	float prev_rotation;
	float rotation_vel;
	bool dead;
	std::string tag;
	int health;
};

