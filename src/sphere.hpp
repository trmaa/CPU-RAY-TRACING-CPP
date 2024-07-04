#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <cmath>
#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>
#include "./ray.hpp"
#include "./material.hpp"

struct Sphere {
	glm::vec3 center;
	float radius;
	Material material;

	Sphere(glm::vec3 o, float r, glm::vec3 c): center(o), radius(r), material(c) {}
	~Sphere() = default;

	const float checkCollision(const Ray* ray) const { 
		glm::vec3 oc = ray->origin - this->center;
		float a = glm::dot(ray->direction, ray->direction);
		float b = 2.0f * glm::dot(oc, ray->direction);
		float c = glm::dot(oc, oc) - this->radius * this->radius;
		float discriminant = b * b - 4 * a * c;

		if (discriminant < 0) {
			return -1.0f;
		}

		float sqrtDiscriminant = std::sqrt(discriminant);
		float t1 = (-b - sqrtDiscriminant) / (2.0f * a);
		float t2 = (-b + sqrtDiscriminant) / (2.0f * a);

		if (t1 > 0.0f && t2 > 0.0f) {
			return std::min(t1, t2);
		} else if (t1 > 0.0f) {
			return t1;
		} else if (t2 > 0.0f) {
			return t2;
		} else {
			return -1.0f;
		}
	}
};

#endif
