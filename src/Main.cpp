#include "Scene.hpp"
#include "Camera.hpp"
#include "Color.hpp"
#include "HitRecord.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"
#include "Metal.hpp"
#include "PointLight.hpp"
#include "SolidColorTexture.hpp"
#include "Dielectric.hpp"

using namespace raytracer::rendering;
using namespace raytracer::geometry;
using namespace raytracer::lighting;
using namespace raytracer::material;

Color computeDirectLighting(HitRecord& record, const Scene& scene) {

	Color totalColor = Color::black;

	for (const auto& light : scene.getLights())
	{
		glm::vec3 lightDirection = glm::normalize(light->position - record.point);
		float lightDistance = glm::length(light->position - record.point);

		Ray shadowRay(record.point + record.normal * 0.001f, lightDirection);
		HitRecord shadowRecord;

		bool inShadow = scene.intersect(shadowRay, shadowRecord) && shadowRecord.t < lightDistance;
		if (!inShadow) {
			float diffuse = std::max(glm::dot(lightDirection, record.normal), 0.0f);
			totalColor = totalColor + ((*light).getIllumination(shadowRay, lightDistance)
				* (*record.material).getTextureAlbedo(record.point, record.u, record.v)) * diffuse;

		}
	}
	totalColor.clamp();
	return totalColor;
}


Color traceRay(const Ray& ray, const Scene& scene, int depth)
{
	if (depth <= 0) {
		return Color::black;
	}

	HitRecord record;
	if (scene.intersect(ray, record)) {
		Color directLighting = computeDirectLighting(record, scene);

		Ray scattered;
		Color attenuation;
		Color emitted = (*record.material).getTextureEmission(record.point, record.u, record.v);

		if ((*record.material).scatter(ray, record, attenuation, scattered)) {
			Color indirectLighting = attenuation * traceRay(scattered, scene, depth - 1);
			return emitted + directLighting + indirectLighting;
		}
		else {
			return emitted + directLighting;
		}
	}
	else {
		return scene.backgroundColor;
	}
}

float randomFloat() {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_real_distribution<float> dis(0.0f, 1.0f);
	return dis(gen);
}

// Returns false if the window was closed during the render
bool RenderScene(const Scene& scene, Camera& camera, int samplesPerPixel)
{
	for (int y = 0; y < HEIGHT; y++)
	{
		// Keep the window responsive while rendering
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				return false;
			}
		}

		for (int x = 0; x < WIDTH; x++)
		{
			Color pixelColor = Color::black;

			for (int s = 0; s < samplesPerPixel; s++) {
				float u = (x + randomFloat()) / WIDTH;
				float v = 1.0f - (y + randomFloat()) / HEIGHT;

				Ray ray = camera.getRay(u, v);
				pixelColor = pixelColor + traceRay(ray, scene, scene.maxDepth);
			}

			pixelColor = pixelColor / (float)samplesPerPixel;
			pixelColor.clamp();

			SDL_SetRenderDrawColor(scene.renderer,
				(Uint8)(pixelColor.r * 255.0f + 0.5f),
				(Uint8)(pixelColor.g * 255.0f + 0.5f),
				(Uint8)(pixelColor.b * 255.0f + 0.5f), 255);
			SDL_RenderPoint(scene.renderer, (float)x, (float)y);
		}

		printf("Rendering: %d%%\r", (y + 1) * 100 / HEIGHT);
	}
	printf("\n");
	return true;
}

int main()
{
	Scene scene(Color(0.80f, 0.87f, 0.96f), 10);
	if (!scene.initialize()) {
		return 1;
	}

	// Ground: a huge, slightly blurry reflective sphere
	auto texture = std::make_shared<SolidColorTexture>(Color(0.68f, 0.71f, 0.78f));
	auto material = std::make_shared<Metal>(Color::metallic, 0.05f, texture);
	auto sphere = std::make_shared<Sphere>(glm::vec3(0, -1000, 0), 1000.0f, material);
	scene.addObject(sphere);

	texture = std::make_shared<SolidColorTexture>(Color::red);
	material = std::make_shared<Metal>(Color::metallic, 0.03f, texture);
	sphere = std::make_shared<Sphere>(glm::vec3(-3.7f, 1.0f, -0.6f), 1.0f, material);
	scene.addObject(sphere);

	texture = std::make_shared<SolidColorTexture>(Color::yellow);
	material = std::make_shared<Metal>(Color::metallic, 0.03f, texture);
	sphere = std::make_shared<Sphere>(glm::vec3(-1.7f, 0.8f, -2.3f), 0.8f, material);
	scene.addObject(sphere);

	texture = std::make_shared<SolidColorTexture>(Color::green);
	material = std::make_shared<Metal>(Color::metallic, 0.03f, texture);
	sphere = std::make_shared<Sphere>(glm::vec3(2.5f, 1.0f, -2.0f), 1.0f, material);
	scene.addObject(sphere);

	texture = std::make_shared<SolidColorTexture>(Color::blue);
	material = std::make_shared<Metal>(Color::metallic, 0.03f, texture);
	sphere = std::make_shared<Sphere>(glm::vec3(4.1f, 0.9f, -0.2f), 0.9f, material);
	scene.addObject(sphere);

	// Slightly blue tint so the glass sphere stands out
	texture = std::make_shared<SolidColorTexture>(Color(0.85f, 0.93f, 1.0f));
	auto dialec = std::make_shared<Dielectric>(1.5f, 0.5f, texture);
	sphere = std::make_shared<Sphere>(glm::vec3(0.6f, 1.3f, 1.0f), 1.3f, dialec);
	scene.addObject(sphere);

	auto light = std::make_shared<PointLight>(glm::vec3(-5, 9, 6), 0.7f, Color::naturalLight, 1.0f, 0.0f, 0.002f);
	scene.addLight(light);

	Camera camera(glm::vec3(0, 2.2f, 11.0f), 32);
	camera.setLookAt(glm::vec3(0.3f, 1.0f, 0));

	if (RenderScene(scene, camera, 400)) {
		SDL_RenderPresent(scene.renderer);

		// Keep the picture on screen until the window is closed
		SDL_Event event;
		while (SDL_WaitEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				break;
			}
		}
	}

	scene.kill();
	return 0;
}
