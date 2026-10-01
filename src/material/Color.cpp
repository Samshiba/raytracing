#include "Color.hpp"

using namespace raytracer::material;

Color::Color(float r, float g, float b, float a)
{
	this->r = (float) r;
	this->g = (float) g;
	this->b = (float) b;
	this->a = (float) a;
}

Color::Color(glm::vec3 color, float a)
{
	this->r = color.r;
	this->g = color.g;
	this->b = color.b;
	this->a = a;
}

Color Color::random()
{
	return Color(glm::vec3(
		rand() / (float)RAND_MAX,
		rand() / (float)RAND_MAX,
		rand() / (float)RAND_MAX));
}


const Color Color::white = Color(1, 1, 1);
const Color Color::black = Color(0, 0, 0);
const Color Color::red = Color(1, 0, 0);
const Color Color::green = Color(0, 1, 0);
const Color Color::blue = Color(0, 0, 1);
const Color Color::yellow = Color(1, 1, 0);
const Color Color::naturalLight = Color(253 / 255.0f, 242 / 255.0f, 200 / 255.0f);
const Color Color::metallic = Color(0.8f, 0.8f, 0.8f);
const Color Color::grey = Color(0.5f, 0.5f, 0.5f);

Color Color::blend(const Color& other)
{
	a = (1 - (1 - a) * (1 - other.a));
	r = (r * (1 - other.a) + other.r * other.a);
	g = (g * (1 - other.a) + other.g * other.a);
	b = (b * (1 - other.a) + other.b * other.a);

	return *this;
}

Color Color::setAlpha(float alpha)
{
	this->a = alpha;
	return *this;
}

void Color::clamp()
{
	r = glm::clamp(r, 0.0f, 1.0f);
	g = glm::clamp(g, 0.0f, 1.0f);
	b = glm::clamp(b, 0.0f, 1.0f);
	a = glm::clamp(a, 0.0f, 1.0f);
}

Color Color::operator+(const Color& other) const
{
	return Color(r + other.r, g + other.g, b + other.b, a + other.a);
}

Color Color::operator*(const Color& other) const
{
	return Color(r * other.r, g * other.g, b * other.b, a * other.a);
}

Color Color::operator*(float scalar) const
{
	return Color(r * scalar, g * scalar, b * scalar, a);
}

Color Color::operator/(float scalar) const
{
	return Color(r / scalar, g / scalar, b / scalar, a);
}

bool Color::operator!=(const Color& other) const
{
	return r != other.r || g != other.g || b != other.b;
}

bool raytracer::material::Color::operator==(const Color& other) const
{
	return r == other.r && g == other.g && b == other.b;
}

Color Color::lerp(const Color& a, const Color& b, float t)
{
	return a * (1 - t) + b * t;
}
