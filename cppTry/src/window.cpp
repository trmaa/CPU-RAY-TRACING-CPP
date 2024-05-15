#include <iostream>
#include "window.hpp"
#include "camera.hpp"
#include "sphere.hpp"

glm::vec2 Window::viewport(1280,720);
sf::RenderWindow Window::display(sf::VideoMode(Window::viewport.x, Window::viewport.y), "Neo(n) Wyrd");
sf::Image Window::image = sf::Image();

void Window::run() {
    sf::Image& img = Window::image;

	//std::for_each(); TO DO
    for (int x = 0; x < Window::viewport.x; ++x) {
        for (int y = 0; y < Window::viewport.y; ++y) {
			int index = x+y*Window::viewport.x;
			Ray* currentr = &Camera::ray[index];
			Camera::cast(currentr);
			glm::vec3 col((currentr.direction().x*255/Window::viewport.x),(currentr.direction().y*255/Window::viewport.y),0);
			float t = Sphere::collission(currentr);
			if(t>0){
				std::cout<<"bien"<<std::endl;
				col = glm::vec3(255,255,255);
			}
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
