#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
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

	Camera(int w, int h): m_possition(0), m_angle(0), m_direction(0), m_speed(10) {
		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				this->m_ray.push_back(Ray(
					this->m_possition,
					glm::vec3(x-w/2, y-h/2, 500)
				));
			}
		}	
	}
	~Camera() = default;
public:
	void cast(int id){
		this->m_ray[id].origin = this->m_possition;
	}
	void move(float* dt, sf::Event* ev);
};

#endif
