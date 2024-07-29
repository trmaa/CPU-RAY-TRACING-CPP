#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "object.hpp"
#include "ray.hpp"
#include <glm/ext/vector_float3.hpp>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <string>

struct Triangle: public Object{
	Triangle(glm::vec3 ce, glm::vec3 v[2], glm::vec3 c, float e, float r, std::string pa)
        : Object(ce, v, c, e, r, pa) {}
	~Triangle() = default;

	const float checkCollision(const Ray& ray) const override {
		float denom = glm::dot(this->normal, ray.direction);
		
		if (std::abs(denom) < 0.0001f) {
			return -1.0f;
		}

		glm::vec3 plane_to_ray_origin = ray.origin - this->center;
		float t = -glm::dot(this->normal, plane_to_ray_origin) / denom;
		
		return t;
	}
};

#endif
