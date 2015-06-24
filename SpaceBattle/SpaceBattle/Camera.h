#pragma once
#include <SFML\Graphics.hpp>

#include <glm\vec2.hpp>

class Camera
{
public:
	Camera(const sf::FloatRect& view_rect, glm::vec2 centre);
	~Camera();
	sf::View get_view() const;
	void set_centre(const glm::vec2& new_centre);
	void move_view(const glm::vec2& offset);
private:
	sf::View view;
};

