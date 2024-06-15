#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <glm/glm.hpp>
#include "./ray.hpp"

struct Sphere {
	glm::vec3 center;
	float radius;

	Sphere(glm::vec3 o, float r): center(o), radius(r) {}
	~Sphere() = default;

	bool checkColission(Ray* ray) { 
		glm::vec3 oc = this->center - ray->origin;
		float a = glm::dot(ray->direction, ray->direction);
		float b = -2.0 * glm::dot(ray->direction, oc);
		float c = glm::dot(oc, oc) - this->radius*this->radius;
		float disc = b*b - 4*a*c;
		return (disc>=0); 
	}
};

#endif
