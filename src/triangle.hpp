#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "./object.hpp"
#include "ray.hpp"
#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>
#include <string>

struct Triangle: public Object{
	Triangle(glm::vec3 v[3], glm::vec3 c, float e, float r, std::string pa): Object(v, c, e, r, pa) {
        for (int i = 0; i < 3; ++i) {
            vertex[i] = v[i];
        }
    }
	~Triangle() = default;

	const float checkCollision(const Ray* ray) const override {
		return 0;
	}  
};

#endif
