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
    glm::vec3 _position;
    glm::vec3 _angle;
    glm::vec3 _direction;

    float _far = 200;

    float _speed;

public:
    std::vector<Ray> ray;
    const glm::vec3& position() const { return _position; }
    const glm::vec3& direction() {
        this->_direction = glm::vec3(
            -std::sin(this->_angle.x)*std::cos(this->_angle.y),
            -std::cos(this->_angle.x),
            std::sin(this->_angle.x)*std::sin(this->_angle.y)
        );
        return _direction;
    }
    const glm::vec3& angle() { return this->_angle; }

    Camera(const int& w, const int& h)
        : _position(-22.2f,-65.f, 133.2f), 
        _angle(glm::vec3(0.4f, 4.9f, 0.0f)), 
        _direction(0.0f), _speed(100.0f), _far(400.f*w/192) {
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                ray.push_back(Ray(
                    _position,
                    glm::vec3(x - w / 2, y - h / 2, this->_far)
                ));
            }
        }
    }
    ~Camera() = default;

public:
    void cast(int& x, int& y, glm::ivec2& buff_v) {
        int id = (x) + (y) * buff_v.x;

        glm::vec3 idle((x) - buff_v.x / 2, (y) - buff_v.y / 2, this->_far);
        glm::vec3 idleA(
            std::atan2(idle.y, idle.z),
            std::atan2(idle.x, idle.z),
            0.0f
        );
        glm::vec3 ang = _angle + idleA;
        glm::vec3 direction(
            2000.0f * std::cos(ang.x) * std::cos(ang.y),
            2000.0f * std::sin(ang.x),
            2000.0f * std::cos(ang.x) * std::sin(ang.y)
        );

        ray[id] = Ray(_position, direction);
    }

    void move(float& dt, sf::Event& ev) {
        float fixedSpeed = _speed * (dt);
        if (ev.type != sf::Event::KeyPressed) {
            return;
        }
        if (ev.key.code == sf::Keyboard::Up) {
            _position.x += std::cos(_angle.y) * fixedSpeed;
            _position.z += std::sin(_angle.y) * fixedSpeed;
        }
        if (ev.key.code == sf::Keyboard::Down) {
            _position.x -= std::cos(_angle.y) * fixedSpeed;
            _position.z -= std::sin(_angle.y) * fixedSpeed;
        }
        if (ev.key.code == sf::Keyboard::Left) {
            _position.x += std::cos(_angle.y - 3.14159f / 2) * fixedSpeed;
            _position.z += std::sin(_angle.y - 3.14159f / 2) * fixedSpeed;
        }
        if (ev.key.code == sf::Keyboard::Right) {
            _position.x -= std::cos(_angle.y - 3.14159f / 2) * fixedSpeed;
            _position.z -= std::sin(_angle.y - 3.14159f / 2) * fixedSpeed;
        }
        if (ev.key.code == sf::Keyboard::RControl) {
            _position.y -= fixedSpeed;
        }
        if (ev.key.code == sf::Keyboard::RShift) {
            _position.y += fixedSpeed;
        }
        if (ev.key.code == sf::Keyboard::LAlt) {
            _angle.y += 0.1f;
        }
        if (ev.key.code == sf::Keyboard::LShift) {
            _angle.y -= 0.1f;
        }
        if (ev.key.code == sf::Keyboard::LControl) {
            _angle.x += 0.1f;
        }
        if (ev.key.code == 40) {
            _angle.x -= 0.1f;
        }
    }
};

#endif
