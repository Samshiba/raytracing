#pragma once

#include "General.hpp"
#include "Texture.hpp"
#include "Ray.hpp"
#include "HitRecord.hpp"
#include "Color.hpp"

namespace raytracer {
    namespace material{
        class Material {
        public:
            std::shared_ptr<Texture> texture;

            virtual ~Material() = default;

            /**
            * @brief Scatter a ray
            *
            * @param ray The incoming ray that hit the object
            * @param record The hit record of this ray
            * @param attenuation The attenuation of the ray
            * @param scattered The new scattered ray
            *
            * @return true If the ray was scattered, false if it was absorbed
            */
            virtual bool scatter(const geometry::Ray& ray, const geometry::HitRecord& record,
                Color& attenuation, geometry::Ray& scattered) const = 0;

            virtual raytracer::material::Color getTextureAlbedo(const glm::vec3& point, float u, float v) const;
            virtual raytracer::material::Color getTextureEmission(const glm::vec3& point, float u, float v) const;

        };
	}
}