#pragma once

#include <glm\vec2.hpp>

namespace sf
{
	class RenderWindow;
}

namespace MATT_SPENCER_HELPER_NAMESPACE
{
	float deg_to_rad(const float deg);
	float rad_to_deg(const float rad);
	glm::vec2 lerp(const glm::vec2& v0, const glm::vec2& v1, float t);
	float lerp(float a, float b, float t);
	float clamp(float min, float max, float x);
	void draw_vec(sf::RenderWindow& window, const glm::vec2& v0, const glm::vec2 v1);
	const double PI = 3.14159265359;
}