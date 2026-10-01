#include "Metal.hpp"

using namespace raytracer::geometry;
using namespace raytracer::material;

Metal::Metal(const Color& attenuationAlbedo, float fuzziness, std::shared_ptr<Texture> texture)
	: attenuationAlbedo(attenuationAlbedo), fuzziness(fuzziness) {
	this->texture = texture;
}

bool Metal::scatter(const Ray& ray, const HitRecord& record, Color& attenuation, Ray& scattered) const
{
	glm::vec3 reflected = glm::reflect(glm::normalize(ray.direction), record.normal);

	scattered = Ray(record.point + record.normal * 0.001f, reflected + fuzziness * glm::sphericalRand(1.0f));
	// Partially tinted by the texture so colored metals still reflect each other
	attenuation = Color::lerp(attenuationAlbedo, getTextureAlbedo(record.point, record.u, record.v), 0.6f);

	return glm::dot(scattered.direction, record.normal) > 0;
}
