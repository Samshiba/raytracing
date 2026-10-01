#pragma once

#include "General.hpp"

namespace raytracer {
	namespace geometry {
		class HitRecord {
		public:
			float t;
			glm::vec3 point;
			glm::vec3 normal;
			float u, v;
			std::shared_ptr<material::Material> material;
			bool frontFace;

			HitRecord();

		};

	}
}
