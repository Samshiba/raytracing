#pragma once

#define _USE_MATH_DEFINES
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <limits>
#include <memory>
#include <random>
#include <vector>

#include <SDL3/SDL.h>

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/random.hpp>

constexpr int WIDTH = 1280;
constexpr int HEIGHT = 720;

namespace raytracer {
	namespace geometry {
		class Ray;
		class HitRecord;
		class Object;
	}
	namespace material {
		class Color;
		class Texture;
		class Material;
	}
	namespace lighting {
		class Light;
	}
	namespace rendering {
		class Scene;
		class Camera;
	}
}
