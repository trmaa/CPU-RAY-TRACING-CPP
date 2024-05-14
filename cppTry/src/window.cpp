#include "window.hpp"

glm::vec2 Window::viewport(1280,720);
sf::RenderWindow Window::display(sf::VideoMode(Window::viewport.x, Window::viewport.y), "Neo(n) Wyrd");
sf::Image Window::image = sf::Image();

void Window::run() {
    sf::Image& img = Window::image;

	//std::for_each(); TO DO
    for (int x = 0; x < Window::viewport.x; ++x) {
        for (int y = 0; y < Window::viewport.y; ++y) {
			glm::vec3 col((x*255/Window::viewport.x),(y*255/Window::viewport.y),0);
            sf::Color color(col.r, col.g, col.b);
            img.setPixel(x, y, color);
        }
    }

    sf::Texture texture;
    texture.loadFromImage(img);
    sf::Sprite sprite(texture);

	Window::display.clear();
    Window::display.draw(sprite);
    Window::display.display(); 
}
