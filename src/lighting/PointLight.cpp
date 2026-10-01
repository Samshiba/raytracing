#include "PointLight.hpp"

using namespace raytracer::lighting;
using namespace raytracer::geometry;
using namespace raytracer::material;

PointLight::PointLight(const glm::vec3& position, float intensity, Color color,
	float constantAttenuation, float linearAttenuation, float quadraticAttenuation) :
	Light(position, intensity, color, constantAttenuation, linearAttenuation, quadraticAttenuation) {
}

Color PointLight::getIllumination(Ray& /*ray*/, float distance) const
{
	return color * intensity * getAttenuation(distance);
}

