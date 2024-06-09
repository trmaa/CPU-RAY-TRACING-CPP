#ifndef WINDOW_HPP
#define WINDOW_HPP

#include<SFML/Graphics.hpp>
#include<cmath>
#include<glm/glm.hpp>

class Window{
private:
	static sf::Image m_buffer;

	static sf::Font m_font;
	static sf::Text m_fpsText;
public:
	static sf::RenderWindow window;
	static const glm::ivec2 viewport(){
		return glm::ivec2(std::round(Window::window.getSize().x), std::round(Window::window.getSize().y));
	}
public:
	static void open();
	static void repaint(float dt);
};

#endif
