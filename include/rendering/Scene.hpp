#pragma once

#include "General.hpp"
#include "Object.hpp"
#include "Light.hpp"
#include "Material.hpp"

namespace raytracer {
    namespace rendering {
        class Scene {
		public:
			material::Color backgroundColor;
			int maxDepth;

			SDL_Window* window;
			SDL_Renderer* renderer;

			Scene(material::Color backgroundColor, int maxDepth);	

			std::vector< std::shared_ptr<geometry::Object>> getObjects() const;
			const std::vector< std::shared_ptr<lighting::Light>>& getLights() const;

			void addObject(std::shared_ptr<geometry::Object> object);
            void addLight(std::shared_ptr<lighting::Light> light);

			bool intersect(const geometry::Ray& ray, geometry::HitRecord& record) const;

			bool initialize();
			void kill();

        private:
			std::vector< std::shared_ptr<geometry::Object>> objects;
            std::vector< std::shared_ptr<lighting::Light>> lights;

        };
    }
}