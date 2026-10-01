#include "Camera.hpp"

using namespace raytracer::geometry;
using namespace raytracer::rendering;

Camera::Camera(const glm::vec3& origin, float fov)
	: origin(origin), fov(fov), aspectRatio(WIDTH / (float)HEIGHT) {
	this->theta = glm::radians(fov);
	this->lookAt = glm::vec3(0, 0, -1);
	update();
}

float Camera::getAspectRatio() const {
	return aspectRatio;
}

float Camera::getTheta() const {
	return theta;
}

void Camera::setOrigin(const glm::vec3& newOrigin) {
	this->origin = newOrigin;
	update();
}

void Camera::setLookAt(const glm::vec3& newLookAt) {
	this->lookAt = newLookAt;
	update();
}

void Camera::setFov(float newFov) {
	this->fov = newFov;
	this->theta = glm::radians(newFov);
	update();
}

void Camera::update() {
	// Calculate half of the viewport height and width based on the fov
	float halfHeight = glm::tan(this->theta / 2);
	float halfWidth = aspectRatio * halfHeight;

	glm::vec3 w = glm::normalize(origin - lookAt);  // Backward vector
	glm::vec3 up = glm::vec3(0, 1, 0);  // World up direction
	glm::vec3 u = glm::normalize(glm::cross(up, w));  // Horizontal vector
	glm::vec3 v = glm::cross(w, u);  // Vertical vector

	this->horizontal = u * (halfWidth * 2);
	this->vertical = v * (halfHeight * 2);
	this->lowerLeftCorner = origin - u * halfWidth - v * halfHeight - w;
}

Ray Camera::getRay(float s, float t) {
	return Ray(origin, lowerLeftCorner + horizontal * s + vertical * t - origin);
}