#pragma once

#include "General.hpp"

namespace raytracer {
	namespace material {
		class Color {
		public:
			float r, g, b, a;

			Color(float r, float g, float b, float a = 1.0f);
			Color(glm::vec3 color, float a = 1.0f);
			Color() = default;

			static Color random();

			Color operator+(const Color& other) const;
			Color operator*(const Color& other) const;
			Color operator*(float scalar) const;
			Color operator/(float scalar) const;
			bool operator!=(const Color& other) const;
			bool operator==(const Color& other) const;

			static Color lerp(const Color& a, const Color& b, float t);

			void clamp();
			Color blend(const Color& other);

			Color setAlpha(float a);

			static const Color white;
			static const Color black;
			static const Color red;
			static const Color green;
			static const Color blue;
			static const Color yellow;
			static const Color naturalLight;
			static const Color metallic;
			static const Color grey;
		};
	}
}