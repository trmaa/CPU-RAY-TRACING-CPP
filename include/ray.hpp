#ifndef RAY_HPP
#define RAY_HPP

#include <glm/glm.hpp>

struct Ray {
    glm::vec3 origin;
    glm::vec3 direction;

    Ray(glm::vec3 o, glm::vec3 d): origin(o), direction(d) {}
    ~Ray() = default;

    const glm::vec3 f(const float x) const { return this->origin + x*this->direction; }
};

#endif
