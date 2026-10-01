#pragma once

#include "Light.hpp"

namespace raytracer {
    namespace lighting {
        class PointLight : public Light {
        public:

			PointLight(const glm::vec3 &position, float intensity, material::Color color,
                float constantAttenuation = 1.0f, float linearAttenuation = 0.0f, float quadraticAttenuation = 0.0f);

			material::Color getIllumination(geometry::Ray& ray, float distance) const override;
        };
    }
}