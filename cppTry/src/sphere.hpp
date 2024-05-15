#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <glm/glm.hpp>
#include "ray.hpp"

struct Sphere{
	static glm::vec3 possition;
	static float radius;

	static float collission(Ray ray);
};

#endif
