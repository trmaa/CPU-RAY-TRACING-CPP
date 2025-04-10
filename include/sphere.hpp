#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <cmath>
#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>
#include "ray.hpp"
#include "object.hpp"

struct Sphere: public Object {
    Sphere(const glm::vec3& cen, float rad, const glm::vec3& c, float e, float ro, const std::string& p)
	: Object(cen, rad, c, e, ro, p) {}
    ~Sphere() = default;

    const float checkCollision(const Ray& ray) const override { 
	glm::vec3 oc = ray.origin - this->center;
	float a = glm::dot(ray.direction, ray.direction);
	float b = 2.0f * glm::dot(oc, ray.direction);
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

    const std::string type() const override {
	return "Sphere";
    }
};

#endif
