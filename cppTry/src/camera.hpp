#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <vector>
struct Camera{
	static glm::vec3 possition;
	static glm::vec3 angle;
	static std::vector<glm::vec2> ray;

	static void start();
};

#endif
