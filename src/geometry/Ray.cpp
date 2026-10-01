#include "Ray.hpp"

using namespace raytracer::geometry;

Ray::Ray(const glm::vec3& origin, const glm::vec3& direction)
	: origin(origin), direction(direction) {
}