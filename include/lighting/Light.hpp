#pragma once

#include "General.hpp"
#include "Color.hpp"
#include "Ray.hpp"


namespace raytracer {
    namespace lighting {
        class Light {
        public:
            glm::vec3 position;
			float intensity; // Mapped to [0, 1]
            float constantAttenuation;
            float linearAttenuation;
            float quadraticAttenuation;
            material::Color color;

            virtual ~Light() = default;
			Light(const glm::vec3& position, float intensity, const material::Color& color,
				float constantAttenuation, float linearAttenuation, float quadraticAttenuation);

			virtual float getAttenuation(float distance) const;

            virtual material::Color getIllumination(geometry::Ray& ray, float distance) const = 0;

        };
    }
}