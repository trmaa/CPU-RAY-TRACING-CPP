#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include "window.hpp"
#include "camera.hpp"
#include "scene.hpp"

static int w = static_cast<int>(16*15);
static int h = static_cast<int>(9*15);
int scene_id = 1;
Scene scn("./bin/scene.json", w, h);
Window win(w, h, "rtx");
Camera cam(w, h);

void loop(float& dt, sf::Event& ev) {
    win.repaint(dt, cam, scn, ev);
    cam.move(dt, ev);

    if (ev.key.code == sf::Keyboard::Tab) {
		scn = Scene("./bin/scene.json", w, h);
	}
    if (ev.key.code == sf::Keyboard::F1) {
        scene_id++;
        if (scene_id > 8) {
            scene_id = 1;
        }
        std::string command = "./scripts/change_scene.sh " + std::to_string(scene_id);
        std::system(command.c_str());
	}
}

int main(int argc, char* argv[]) {
    std::cout << "starting..." << std::endl;

    sf::Clock clck;
    sf::Event ev;
    sf::Time elapsed;
    float dt;
    while (win.isOpen()) { 
        while (win.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed) {
                win.close();
            } else if (ev.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, ev.size.width, ev.size.height);
                win.setView(sf::View(visibleArea));
            }
        }
        elapsed = clck.restart();
        dt = elapsed.asSeconds();

        loop(dt, ev);
    }

    std::system("clear");
}
