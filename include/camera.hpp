#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_int2.hpp>
#include <glm/glm.hpp>
#include <vector>
#include "ray.hpp"

class Camera {
private:
    glm::vec3 m_position;
    glm::vec3 m_angle;
    glm::vec3 m_direction;

    float m_far = 200;

    float m_speed;

public:
    std::vector<Ray> ray;
    const glm::vec3& position() const { return m_position; }
    const glm::vec3& direction();

	Camera(int w, int h);
    ~Camera() = default;

public:
    void cast(int& x, int& y, glm::ivec2& buff_v);
    void move(float& dt, sf::Event& ev);
};

#endif
