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
			
			glm::vec3 hitp = ray.f(t);
            
            glm::vec3 v0 = this->sides[0];
            glm::vec3 v1 = this->sides[1];
            glm::vec3 v2 = hitp - this->center;

            float d00 = glm::dot(v0, v0);
            float d01 = glm::dot(v0, v1);
            float d11 = glm::dot(v1, v1);
            float d20 = glm::dot(v2, v0);
            float d21 = glm::dot(v2, v1);
            float denom = d00 * d11 - d01 * d01;

            float v = (d11 * d20 - d01 * d21) / denom;
            float w = (d00 * d21 - d01 * d20) / denom;
            float u = 1.0f - v - w;

            bool cond = (u >= 0.f) && (v >= 0.f) && (w >= 0.f);
            if (cond && t >= 0.f) {
                return t;
            }
		}

		return -1.f;
	}

	const std::string type() const override {
		return "Triangle";
	}
};

#endif
