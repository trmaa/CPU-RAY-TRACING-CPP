#include "../include/camera.hpp"

void Camera::move(float* dt, sf::Event* ev) {
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
