#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

struct Window{
	static sf::RenderWindow display; 
	static glm::vec2 viewport;
	static sf::Image image; 
	
	static void run();
};

#endif
