#include "SolidColorTexture.hpp"

using namespace raytracer::material;

SolidColorTexture::SolidColorTexture(const Color& color) : albedo(color) {
}

Color SolidColorTexture::getAlbedo(float /*u*/, float /*v*/, const glm::vec3& /*point*/) const
{
	return albedo;
}
