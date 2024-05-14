#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include "ray.hpp"

struct Camera{
	static glm::vec3 possition;
	static glm::vec3 angle;
	static Ray ray[];

	static void cast_ray(glm::vec2 id);
};

#endif
