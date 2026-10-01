#include "Scene.hpp"

using namespace raytracer::rendering;
using namespace raytracer::geometry;
using namespace raytracer::lighting;
using namespace raytracer::material;

Scene::Scene(Color backgroundColor, int maxDepth)
	: backgroundColor(backgroundColor), maxDepth(maxDepth) {
}

const std::vector<std::shared_ptr<Object>>& Scene::getObjects() const
{
	return this->objects;
}

const std::vector<std::shared_ptr<Light>>& Scene::getLights() const
{
	return this->lights;
}

void Scene::addObject(std::shared_ptr<Object> object)
{
	this->objects.push_back(object);
}

void Scene::addLight(std::shared_ptr<Light> light)
{
	this->lights.push_back(light);
}

bool Scene::intersect(const Ray& ray, HitRecord& record) const
{
	record.t = std::numeric_limits<float>::max();
	bool hit = false;

	for (const auto& object : this->objects) {
		HitRecord tempRecord;
		if (object->intersect(ray, tempRecord) && tempRecord.t < record.t) {
			record = tempRecord;
			hit = true;
		}
	}
	return hit;
}

bool Scene::initialize()
{
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
		return false;
	}

	if (!SDL_CreateWindowAndRenderer("raytracing", WIDTH, HEIGHT, 0, &window, &renderer)) {
		SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
		return false;
	}

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    return true;
}

void Scene::kill()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
