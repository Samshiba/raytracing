#pragma once

#include "General.hpp"
#include "Ray.hpp"
#include "HitRecord.hpp"
#include "Material.hpp"
#include "Color.hpp"

namespace raytracer {
	namespace geometry {
		class Object {
		public:
			std::shared_ptr<raytracer::material::Material> material;

			virtual ~Object() = default;

			virtual bool intersect(const Ray& ray, HitRecord& record) const = 0;
			virtual glm::vec3 getNormal(const glm::vec3& point) const = 0;

			/**
			* @brief Compute the UV coordinates of a point on the object
			* @brief (map a 3D point to a 2D point)
			* 
			* @param point The point to compute the UV coordinates of
			* @param u The u coordinate of the point
			* @param v The v coordinate of the point
			* 
			*/
			virtual void computeUV(const glm::vec3& point, float& u, float& v) const = 0;
		};

	}
}
 