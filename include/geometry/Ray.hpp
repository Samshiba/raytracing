#pragma once

#include "General.hpp"

namespace raytracer {
	namespace geometry {
		class Ray {
		public:
			glm::vec3 origin;
			glm::vec3 direction;

			Ray(const glm::vec3& origin, const glm::vec3& direction);

			Ray() = default;
		};

	}
}
