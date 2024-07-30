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
		// Calculate the denominator of the intersection formula
		float denominator = glm::dot(ray.direction, this->normal);

		// Check if the ray is parallel to the plane
		if (glm::abs(denominator) > 1e-6) { // Use a small epsilon to avoid division by zero
			// Calculate the numerator of the intersection formula
			glm::vec3 diff = this->center - ray.origin;
			float t = glm::dot(diff, this->normal) / denominator;
			
			// Check if t is positive, as we are only interested in intersections in the direction of the ray
			if (t >= 0.0f) {
				return t;
			}
		}

		// If the ray is parallel to the plane or t is negative, there is no intersection
		return -1.0f; // Use -1.0f to indicate no intersection
	}

	const std::string type() const override {
		return "Triangle";
	}
};

#endif
