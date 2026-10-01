#include "Texture.hpp"

using namespace raytracer::material;

Color Texture::getEmission(float /*u*/, float /*v*/, const glm::vec3& /*point*/) const
{
	return Color::black;
}
