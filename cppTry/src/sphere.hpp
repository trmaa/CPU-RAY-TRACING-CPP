#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <glm/glm.hpp>

struct Sphere{
	static glm::vec3 origin;
	static float radius;

	static float colide(glm::vec2 id);
};

#endif
