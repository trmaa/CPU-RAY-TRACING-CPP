#ifndef RAY_HPP
#define RAY_HPP

#include <glm/glm.hpp>

struct Ray{
	static glm::vec3 origin;
	static glm::vec3 direction;

	static glm::vec3 f(int x);
};

#endif
