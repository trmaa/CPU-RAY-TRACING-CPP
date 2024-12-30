#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/Graphics.hpp>
#include <any>
#include <cmath>
#include <glm/glm.hpp>
#include <vector>
#include "SFML/Graphics/RenderWindow.hpp"
#include "ray.hpp"

class Camera {
private:
    glm::vec3 _position;
    glm::vec3 _angle;
    glm::vec3 _direction;

    float _far = 200;

    float _speed;

    float _mouseSensitivity;

    sf::Vector2f _centerPosition;
    bool _mouseLocked;

public:
    bool moving = false;

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
        : _position(2.f,-2.5f, -365.63f), _mouseSensitivity(0.2f), _mouseLocked(false),
        _angle(glm::vec3(0.f, -4.7f, 0.0f)),
        _direction(0.0f), _speed(100.0f), _far(200.f*w/68) {
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

    void lock_mouse(sf::RenderWindow& window) {
        _centerPosition = sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f);
        window.setMouseCursorVisible(false);
        sf::Mouse::setPosition(window.mapCoordsToPixel({ _centerPosition.x, _centerPosition.y }), window);
        _mouseLocked = true;
    }

    void move(const float& dt) {
        glm::vec3 p = _position;

        float fixedSpeed = _speed * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
            fixedSpeed *= 10;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            _position.x -= std::cos(_angle.y) * fixedSpeed;
            _position.z -= std::sin(_angle.y) * fixedSpeed;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            _position.x += std::cos(_angle.y) * fixedSpeed;
            _position.z += std::sin(_angle.y) * fixedSpeed;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            _position.x -= std::sin(_angle.y) * fixedSpeed;
            _position.z += std::cos(_angle.y) * fixedSpeed;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            _position.x += std::sin(_angle.y) * fixedSpeed;
            _position.z -= std::cos(_angle.y) * fixedSpeed;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
            _position.y += fixedSpeed;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            _position.y -= fixedSpeed;
        }

        if (p != _position) {
            this->moving = true;
        } else {
            this->moving = false;
        }
    }

    void handle_mouse_movement(sf::RenderWindow& window) {
        if (!_mouseLocked) {
            lock_mouse(window);
            return;
        }

        sf::Vector2f mousePosition = (sf::Vector2f)sf::Mouse::getPosition(window);
        sf::Vector2f mouseDelta = mousePosition - _centerPosition;

        glm::vec3 a = _angle;

        _angle.y += mouseDelta.x * _mouseSensitivity * 0.0174533f;
        _angle.x += mouseDelta.y * _mouseSensitivity * 0.0174533f;

        if (a != _angle) {
            this->moving = true;
        } else {
            this->moving = false;
        }

        const float maxPitch = 89.0f * 0.0174533f;
        if (_angle.x > maxPitch) _angle.x = maxPitch;
        if (_angle.x < -maxPitch) _angle.x = -maxPitch;

        sf::Mouse::setPosition(window.mapCoordsToPixel({ _centerPosition.x, _centerPosition.y }), window);
    }
};

#endif
