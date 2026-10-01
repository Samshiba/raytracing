#include "Dielectric.hpp"

using namespace raytracer::geometry;
using namespace raytracer::material;

Dielectric::Dielectric(float refractiveIndex, float absorptionCoefficient, std::shared_ptr<Texture> texture)
{
	this->refractiveIndex = refractiveIndex;
	this->absorptionCoefficient = absorptionCoefficient;
	this->texture = texture;
}

float Dielectric::schlick(float cosine, float refractionIndex)
{
	float r0 = (1 - refractionIndex) / (1 + refractionIndex);
	r0 = r0 * r0;
	return r0 + (1 - r0) * powf((1 - cosine), 5);
}

// Glass has no diffuse component: its look comes only from reflection and refraction
Color Dielectric::getTextureAlbedo(const glm::vec3& /*point*/, float /*u*/, float /*v*/) const
{
	return Color::black;
}

bool Dielectric::scatter(const Ray& ray, const HitRecord& record, Color& attenuation, Ray& scattered) const
{
	attenuation = Color(1.0f, 1.0f, 1.0f);

	float refractionRatio = record.frontFace ? (1.0f / refractiveIndex) : refractiveIndex;
	glm::vec3 unitDirection = glm::normalize(ray.direction);

	float cosTheta = std::min(glm::dot(-unitDirection, record.normal), 1.0f);
	float sinTheta = std::sqrt(std::max(0.0f, 1.0f - cosTheta * cosTheta));

	bool cannotRefract = refractionRatio * sinTheta > 1.0f;
	glm::vec3 direction;
	bool reflected = cannotRefract || schlick(cosTheta, refractionRatio) > glm::linearRand(0.0f, 1.0f);

	if (reflected) {
		direction = glm::reflect(unitDirection, record.normal);
	}
	else {
		direction = glm::refract(unitDirection, record.normal, refractionRatio);
		// Only the transmitted light is tinted by the glass
		if (texture) {
			attenuation = texture->getAlbedo(record.u, record.v, record.point);
		}
	}

	// The normal always faces the incoming ray: a reflected ray stays on that side,
	// a refracted ray crosses the surface and must start on the opposite side
	glm::vec3 offset = record.normal * 0.001f;
	scattered = Ray(reflected ? record.point + offset : record.point - offset, direction);
	return true;
}

