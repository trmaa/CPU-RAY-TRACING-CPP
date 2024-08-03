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
		float denominator = glm::dot(ray.direction, this->normal);

		if (glm::abs(denominator) > 1e-6) { 
			glm::vec3 diff = this->center - ray.origin;
			float t = glm::dot(diff, this->normal) / denominator;
			
			if (t >= 0.0f) {
				return t;
			}
		}

		return -1.0f;
	}

	const std::string type() const override {
		return "Triangle";
	}
};

#endif
