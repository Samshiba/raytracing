#pragma once

#include "Object.hpp"

namespace raytracer {
	namespace geometry {
		class Sphere : public Object {
		public:
			glm::vec3 center;
			float radius;

			Sphere(const glm::vec3& center, float radius, 
				std::shared_ptr<raytracer::material::Material> material);

			bool intersect(const Ray& ray, HitRecord& record) const override;
			glm::vec3 getNormal(const glm::vec3& point) const override;

			/**
			* @brief Compute the UV coordinates of a point on the object
			* @brief (map a 3D point to a 2D point between [0, 1])
			*
			* @param point The point to compute the UV coordinates of
			* @param u The u coordinate of the point
			* @param v The v coordinate of the point
			*
			*/
			void computeUV(const glm::vec3& point, float& u, float& v) const override;

		};
	}
}
