#ifndef RAY_HPP
#define RAY_HPP

#include <glm/glm.hpp>

struct Ray{
	Ray() {}
    Ray(const glm::vec3& origin, const glm::vec3& direction) : orig(origin), dir(direction) {}

    const glm::vec3& origin() const  { return orig; }
    const glm::vec3& direction() const { return dir; }

    glm::vec3 f(double t) const {
        return orig + glm::vec3(t)*dir;
    }

    glm::vec3 orig;
	glm::vec3 dir;	
};

#endif
