#include "Light.hpp"

using namespace raytracer::lighting;
using namespace raytracer::material;

Light::Light(const glm::vec3& position, float intensity, const Color& color, float constantAttenuation,
	float linearAttenuation, float quadraticAttenuation) : position(position), intensity(intensity), color(color) {

	this->constantAttenuation = constantAttenuation;
	this->linearAttenuation = linearAttenuation;
	this->quadraticAttenuation = quadraticAttenuation;
}

float Light::getAttenuation(float distance) const
{
	return 1.0f / (constantAttenuation + 
		linearAttenuation * distance +
		quadraticAttenuation * distance * distance);
}
