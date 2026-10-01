#pragma once

#include "Material.hpp"

namespace raytracer {
    namespace material {
        class Dielectric : public Material {
        public:
			Dielectric(float refractiveIndex, float absorptionCoefficient, std::shared_ptr<Texture> texture);

			bool scatter(const geometry::Ray& ray, const geometry::HitRecord& record,
				Color& attenuation, geometry::Ray& scattered) const override;

			Color getTextureAlbedo(const glm::vec3& point, float u, float v) const override;

		private:
			float refractiveIndex;
			float absorptionCoefficient;

			/**
			* @brief Schlick's approximation of Fresnel coefficients to get ratio of reflected light
			*
			* @param cosine The cosine of theta, the angle of incidence
			* @param refractionIndex The refraction index of the material
			*/
			static float schlick(float cosine, float refractionIndex);
        };
    }
}
