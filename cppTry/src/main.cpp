#include "./window.hpp"

void update();

int main() {
	Window::image.create(Window::viewport.x, Window::viewport.y, sf::Color::Black);
	while (Window::display.isOpen()) {
        sf::Event event;
        while (Window::display.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                Window::display.close();
        }
		update();
	}
    return 0;
}

void update(){
	Window::run();
}
