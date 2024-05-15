#ifndef RAY_HPP
#define RAY_HPP

#include <glm/glm.hpp>

struct Ray{
    point3 orig;
    vec3 dir;
	
	Ray() {}
    Ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

    const point3& origin() const  { return orig; }
    const glm::vec3& direction() const { return dir; }

    point3 f(double t) const {
        return orig + t*dir;
    } 
};

#endif
