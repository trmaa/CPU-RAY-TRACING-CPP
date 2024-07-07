#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "./object.hpp"
#include "ray.hpp"
#include <glm/ext/vector_float3.hpp>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <string>

struct Triangle: public Object{
	Triangle(glm::vec3 v[3], glm::vec3 c, float e, float r, std::string pa): Object(v, c, e, r, pa) {
        for (int i = 0; i < 3; ++i) {
            this->vertex[i] = v[i];
        }
		this->normal = glm::normalize(glm::cross(v[0], v[1]));
    }
	~Triangle() = default;

	const float checkCollision(const Ray& ray) const override {
		float D = glm::dot(this->normal, this->vertex[0]);
		float t = ((D-glm::dot(this->normal, ray.origin))/glm::dot(this->normal, ray.direction));

		if(t > 0 || false){
			glm::vec3 hitp = ray.f(t);
			
			glm::vec3 A = this->vertex[0];
			glm::vec3 B = this->vertex[1] + A;
			glm::vec3 C = this->vertex[2] + A;

			glm::vec3 BA = A - B;
			glm::vec3 BC = C - B;
			glm::vec3 BH = hitp - B;

			float ABC = (float)std::acos(glm::dot(BC, BA) / (BA.length() * BC.length()));

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
