#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cstdlib>
#include <glm/ext/vector_float3.hpp>
#include <iostream>
#include <string>
#include "window.hpp"
#include "camera.hpp"
#include "scene.hpp"

static int w = static_cast<int>(16*10);
static int h = static_cast<int>(9*10);
int scene_id = 1;
Scene scn("./bin/scene.json", w, h);
Window win(w, h, "rtx");
Camera cam(w, h);

sf::Clock clck;
sf::Time elapsed;
float dt;

void loop(sf::Event& ev) {
    win.repaint(dt, cam, scn, ev);
    cam.move(dt);
    cam.handle_mouse_movement(win);

    /*
    glm::vec3 pos = cam.position();
    glm::vec3 dir = cam.angle();
    std::cout << "pos: " << std::to_string(pos.x) << " - "
                         << std::to_string(pos.y) << " - "
                         << std::to_string(pos.z) << std::endl;
    std::cout << "dir: " << std::to_string(dir.x) << " - "
                         << std::to_string(dir.y) << " - "
                         << std::to_string(dir.z) << std::endl;
    */

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
    cam.lock_mouse(win);


    while (win.isOpen()) {
        sf::Event ev;
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

        loop(ev);
    }

    std::system("clear");
}
