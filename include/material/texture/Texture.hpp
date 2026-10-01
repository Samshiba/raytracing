#pragma once

#include "General.hpp"
#include "Color.hpp"

namespace raytracer {
    namespace material {
        class Texture {
        public:
            virtual ~Texture() = default;

            virtual Color getAlbedo(float u, float v, const glm::vec3& point) const = 0;

            virtual Color getEmission(float u, float v, const glm::vec3& point) const;
        };
	}
}