#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <vector>
#include "ray.hpp"

struct Camera{
	static glm::vec3 possition;
	static glm::vec3 angle;
	static std::vector<Ray> ray;

	static void start();
	static void cast(Ray* ray);
};

#endif
