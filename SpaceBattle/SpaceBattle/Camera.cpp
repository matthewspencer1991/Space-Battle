#include "Camera.h"

Camera::Camera(const sf::FloatRect& view_rect, glm::vec2 centre) : view(view_rect)
{
	view.reset(view_rect);
}


Camera::~Camera()
{
}

sf::View Camera::get_view() const
{
	return view;
}

void Camera::set_centre(const glm::vec2& new_centre)
{
	view.setCenter(sf::Vector2f(new_centre.x, new_centre.y));
}

void Camera::move_view(const glm::vec2& offset)
{
	view.move(offset.x, offset.y);
}
