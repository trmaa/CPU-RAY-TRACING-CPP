#include<SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include"../includes/window.hpp"

void loop(float dt){
    Window::repaint(dt);
}

int main(){
	Window::open();

    sf::Clock clock;
	while(Window::window.isOpen()){
        sf::Event event;
        while(Window::window.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                Window::window.close();
        }
        sf::Time elapsed = clock.restart();
        float dt = elapsed.asSeconds();

		loop(dt);
	}
}
