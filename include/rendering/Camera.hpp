#pragma once

#include "General.hpp"
#include "Ray.hpp"

namespace raytracer {
    namespace rendering {
        class Camera {
        public:
			glm::vec3 origin;  // Camera position
			glm::vec3 lookAt; // Camera alignment
			float fov; // Field of view in degrees
			glm::vec3 horizontal, vertical; // Camera dimensions
			glm::vec3 lowerLeftCorner; // Lower left corner of the camera


			Camera(const glm::vec3& origin, float fov);

			geometry::Ray getRay(float s, float t);

			float getAspectRatio() const;
			float getTheta() const;

			void setOrigin(const glm::vec3& origin);
			void setLookAt(const glm::vec3& lookAt);
			void setFov(float fov);

		private:
			float aspectRatio;
			float theta;
			

			void update();

        };
    }
}