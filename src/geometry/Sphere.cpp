#include "Sphere.hpp"

using namespace raytracer::geometry;
using namespace raytracer::material;

Sphere::Sphere(const glm::vec3& center,
	float radius, std::shared_ptr<raytracer::material::Material> material) :
	center(center), radius(radius) {
	this->material = material;
}

bool Sphere::intersect(const Ray& ray, HitRecord& record) const {
	glm::vec3 oc = ray.origin - center;

	float A = glm::dot(ray.direction, ray.direction);
	float B = 2 * glm::dot(oc, ray.direction);
	float C = glm::dot(oc, oc) - radius * radius;

	float D = B * B - 4 * A * C;

	if (D < 0) {
		return false;
	}

	float t1 = (-B - sqrt(D)) / (2 * A);
	float t2 = (-B + sqrt(D)) / (2 * A);

	if (t1 >= 0 && t2 >= 0) {
		record.t = t1 < t2 ? t1 : t2;
	}
	else if (t1 >= 0) {
		record.t = t1;
	}
	else if (t2 >= 0) {
		record.t = t2;
	}
	else {
		return false;
	}

	record.point = ray.origin + record.t * ray.direction;
	record.normal = getNormal(record.point);
	record.material = material;

	record.frontFace = glm::dot(ray.direction, record.normal) < 0;
	if (!record.frontFace) {
		record.normal = -record.normal; // Flip the normal for back face
	}
	computeUV(record.point, record.u, record.v);
	return true;
}

glm::vec3 Sphere::getNormal(const glm::vec3& point) const {
	return glm::normalize(point - center);
}

void Sphere::computeUV(const glm::vec3& point, float& u, float& v) const
{
	glm::vec3 dir = glm::normalize(point - center);

	float phi = atan2(dir.z, dir.x);
	float theta = acos(dir.y);

	u = (phi + glm::pi<float>()) / (2 * glm::pi<float>());
	v = theta / glm::pi<float>();
}

