#include "Helper.h"

namespace MATT_SPENCER_HELPER_NAMESPACE
{
	float deg_to_rad(const float deg)
	{
		return deg * PI / 180.00;
	}

	float rad_to_deg(const float rad)
	{
		return rad * 180.00 / PI;
	}

	glm::vec2 lerp(const glm::vec2& v0, const glm::vec2& v1, float t)
	{
		return v0 + (v1 - v0) * t;
	}

	float lerp(float a, float b, float t)
	{
		return (1 - t) * a + t * b;
	}

	float clamp(float min, float max, float x)
	{
		if (x > max)
		{
			return max;
		}
		else if (x < min)
		{
			return min;
		}
		return x;
	}
}