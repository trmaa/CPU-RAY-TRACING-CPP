#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
 
struct Material {
	glm::vec3 color;
	float emission;
	float roughness;

	const sf::Color* col() const { return new sf::Color(this->color.r, this->color.g, this->color.b); }
	
	Material(glm::vec3 c, float e): color(c), emission(e) {}
	~Material() = default;
};

#endif
