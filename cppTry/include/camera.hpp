#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <glm/ext/vector_int2.hpp>
#include <glm/glm.hpp>
#include <vector>
#include "./ray.hpp"

class Camera {
private:
	glm::vec3 m_possition;
	glm::vec3 m_angle;
	glm::vec3 m_direction;

	std::vector<Ray> m_ray;

	float m_speed;
public:
	glm::vec3* possition() { return &this->m_possition; }
	Ray* ray(int id) { return &this->m_ray[id]; }

	Camera(int w, int h): m_possition(0), m_angle(0), m_direction(0), m_speed(100) {
		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				this->m_ray.push_back(Ray(
					this->m_possition,
					glm::vec3(x-w/2, y-h/2, 200)
				));
			}
		}	
	}
	~Camera() = default;
public:
	void cast(int* x, int* y, glm::ivec2* buff_v) {
		int id = (*x) + (*y)*buff_v->x;
		this->m_ray[id] = Ray(
			this->m_possition,
			glm::vec3((*x)-buff_v->x/2, (*y)-buff_v->y/2, 200)
		);
		this->m_ray[id].origin = this->m_possition;
	}
	void move(float* dt, sf::Event* ev) {
		float fixedSpeed = this->m_speed*(*dt);	
		if (ev->type != sf::Event::KeyPressed) {
			return;
		}
		if (ev->key.code == sf::Keyboard::Right) {
			this->m_possition.x += std::cos(this->m_angle.y) * fixedSpeed;
			this->m_possition.z += std::sin(this->m_angle.y) * fixedSpeed;
		}
		if (ev->key.code == sf::Keyboard::Left) {
			this->m_possition.x -= std::cos(this->m_angle.y) * fixedSpeed;
			this->m_possition.z -= std::sin(this->m_angle.y) * fixedSpeed;
		}
		if (ev->key.code == sf::Keyboard::Down) {
			this->m_possition.x += std::cos(this->m_angle.y - 3.14159f / 2) * fixedSpeed;
			this->m_possition.z += std::sin(this->m_angle.y - 3.14159f / 2) * fixedSpeed;
		}
		if (ev->key.code == sf::Keyboard::Up) {
			this->m_possition.x -= std::cos(this->m_angle.y - 3.14159f / 2) * fixedSpeed;
			this->m_possition.z -= std::sin(this->m_angle.y - 3.14159f / 2) * fixedSpeed;
		}
		if (ev->key.code == sf::Keyboard::LAlt) {
			this->m_possition.y -= fixedSpeed;
		}
		if (ev->key.code == sf::Keyboard::LShift) {
			this->m_possition.y += fixedSpeed;
		}
		if (ev->key.code == sf::Keyboard::RShift) {
			this->m_angle.y += 0.1f;
		}
		if (ev->key.code == sf::Keyboard::RControl) {
			this->m_angle.y -= 0.1f;
		}
	}
};

#endif
