#pragma once

#include "Texture.hpp"

namespace raytracer {
    namespace material {
        class SolidColorTexture : public Texture{
        public:

            SolidColorTexture(const Color& color);

            Color getAlbedo(float u, float v, const glm::vec3& point) const override;

        private:
            Color albedo;

        };
    }
}