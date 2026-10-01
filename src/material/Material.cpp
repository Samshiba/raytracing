#include "Material.hpp"

using namespace raytracer::material;

Color Material::getTextureAlbedo(const glm::vec3& point, float u, float v) const {
	if (texture) {
		return texture->getAlbedo(u, v, point);
	}
	return Color::blue;
}

Color Material::getTextureEmission(const glm::vec3& point, float u, float v) const {
	if (texture) {
		return texture->getEmission(u, v, point);
	}
	return Color::black;
}
