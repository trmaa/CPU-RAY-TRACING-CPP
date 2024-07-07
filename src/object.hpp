#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "material.hpp"
#include "ray.hpp"
#include <glm/ext/vector_float3.hpp>

struct Object {
	Material material;
	glm::vec3 center;
	float radius;
	glm::vec3 sides[2];
	glm::vec3 normal;

	Object(const glm::vec3& cen, float rad, glm::vec3 c, float e, float r, const std::string &pa)
        : center(cen), radius(rad), material(c,e,r,pa) {}

    Object(const glm::vec3& cen ,const glm::vec3 verts[2], glm::vec3 c, float e, float r, const std::string &pa)
        : material(c,e,r,pa), center(cen) {
		this->normal = glm::normalize(glm::cross(verts[0], verts[1]));
        std::copy(verts, verts + 2, sides);
    }

    virtual ~Object() = default;

	virtual const float checkCollision(const Ray& ray) const {
		return 0.f;
	}
};

#endif
