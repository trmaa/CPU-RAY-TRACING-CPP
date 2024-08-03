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
    const glm::vec3& direction() {
        this->m_direction = glm::vec3(
            -std::sin(this->m_angle.x)*std::cos(this->m_angle.y),
            -std::cos(this->m_angle.x),
            std::sin(this->m_angle.x)*std::sin(this->m_angle.y)
        );
        return m_direction;
    }

    Camera(int w, int h)
        : m_position(0.0f,0.0f,100.f), m_angle(glm::vec3(0.0f, -3.14159f * 0.5f, 0.0f)), 
        m_direction(0.0f), m_speed(100.0f), m_far(200.f*w/192) {
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                ray.push_back(Ray(
                    m_position,
                    glm::vec3(x - w / 2, y - h / 2, this->m_far)
                ));
            }
        }
    }
    ~Camera() = default;

public:
    void cast(int& x, int& y, glm::ivec2& buff_v) {
        int id = (x) + (y) * buff_v.x;

        glm::vec3 idle((x) - buff_v.x / 2, (y) - buff_v.y / 2, this->m_far);
        glm::vec3 idleA(
            std::atan2(idle.y, idle.z),
            std::atan2(idle.x, idle.z),
            0.0f
        );
        glm::vec3 ang = m_angle + idleA;
        glm::vec3 direction(
            2000.0f * std::cos(ang.x) * std::cos(ang.y),
            2000.0f * std::sin(ang.x),
            2000.0f * std::cos(ang.x) * std::sin(ang.y)
        );

        ray[id] = Ray(m_position, direction);
    }

    void move(float& dt, sf::Event& ev) {
        float fixedSpeed = m_speed * (dt);
        if (ev.type != sf::Event::KeyPressed) {
            return;
        }
        if (ev.key.code == sf::Keyboard::Up) {
            m_position.x += std::cos(m_angle.y) * fixedSpeed;
            m_position.z += std::sin(m_angle.y) * fixedSpeed;
        }
        if (ev.key.code == sf::Keyboard::Down) {
            m_position.x -= std::cos(m_angle.y) * fixedSpeed;
            m_position.z -= std::sin(m_angle.y) * fixedSpeed;
        }
        if (ev.key.code == sf::Keyboard::Left) {
            m_position.x += std::cos(m_angle.y - 3.14159f / 2) * fixedSpeed;
            m_position.z += std::sin(m_angle.y - 3.14159f / 2) * fixedSpeed;
        }
        if (ev.key.code == sf::Keyboard::Right) {
            m_position.x -= std::cos(m_angle.y - 3.14159f / 2) * fixedSpeed;
            m_position.z -= std::sin(m_angle.y - 3.14159f / 2) * fixedSpeed;
        }
        if (ev.key.code == sf::Keyboard::RControl) {
            m_position.y -= fixedSpeed;
        }
        if (ev.key.code == sf::Keyboard::RShift) {
            m_position.y += fixedSpeed;
        }
        if (ev.key.code == sf::Keyboard::LAlt) {
            m_angle.y += 0.1f;
        }
        if (ev.key.code == sf::Keyboard::LShift) {
            m_angle.y -= 0.1f;
        }
        if (ev.key.code == sf::Keyboard::LControl) {
            m_angle.x += 0.1f;
        }
        if (ev.key.code == 40) {
            m_angle.x -= 0.1f;
        }
    }
};

#endif
