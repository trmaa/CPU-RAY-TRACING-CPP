#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "material.hpp"
#include "ray.hpp"
#include <glm/ext/vector_float3.hpp>

struct Object {
	Material material;
	glm::vec3 center;
	float radius;
	glm::vec3 vertex[3];

	Object(const glm::vec3& cen, float rad, glm::vec3 c, float e, float r, const std::string &pa)
        : center(cen), radius(rad), material(c,e,r,pa) {}

    Object(const glm::vec3 verts[3], glm::vec3 c, float e, float r, const std::string &pa)
        : material(c,e,r,pa) {
        std::copy(verts, verts + 3, vertex);
    }

    virtual ~Object() = default;

	virtual const float checkCollision(const Ray* ray) const {
		return 0.f;
	}
};

#endif
