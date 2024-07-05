#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
 
struct Material {
	glm::vec3 color;
	float emission;
	float roughness;

	const sf::Color* col() const { return new sf::Color(this->color.r, this->color.g, this->color.b); }
	
	Material(glm::vec3 c, float e, float r): color(c), emission(e), roughness(r) {}
	~Material() = default;
};

#endif
