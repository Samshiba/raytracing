#pragma once

#include "Material.hpp"

namespace raytracer {
    namespace material {
        class Metal : public Material {
        public:
			Metal(const Color& attenuationAlbedo, float fuzziness, std::shared_ptr<Texture> texture);


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
            bool scatter(const geometry::Ray& ray, const geometry::HitRecord& record,
                Color& attenuation, geometry::Ray& scattered) const override;

        private:
			Color attenuationAlbedo;
			float fuzziness;

        };
    }
}