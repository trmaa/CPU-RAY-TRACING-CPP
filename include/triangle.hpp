#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "./object.hpp"
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
        float D = glm::dot(this->normal, this->center);
		float t = (glm::dot(D-this->normal, ray.origin))/glm::dot(this->normal, ray.direction);

		if(t > 0){
			glm::vec3 hitp = ray.f(t);
			
			glm::vec3 A = this->center;
			glm::vec3 B = this->sides[0] + A;
			glm::vec3 C = this->sides[1] + A;

			glm::vec3 BA = A - B;
			glm::vec3 BC = C - B;
			glm::vec3 BH = hitp - B;

			float ABC = (float)std::acos(glm::dot(BA, BC)) / (BA.length() * BC.length());

			float a = ((BC.y * BH.x) - (BC.x * BH.y)) / ((BC.y * BA.x) - (BC.x * BA.y));
			float b = ((BA.y * BH.x) - (BA.x * BH.y)) / ((BA.y * BC.x) - (BA.x * BC.y));

			if (a >= 0 && b >= 0 && (a + b) <= 1){
				return t;
			}
		}
		return 0;
    }
};

#endif
