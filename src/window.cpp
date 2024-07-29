#include <SFML/Graphics/CircleShape.hpp>
#define ANTIALIASING 0

#include "window.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_int2.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>

Window::Window(int w, int h, std::string text)
    : m_viewport(w, h), m_frames(0), m_acumulation(w * h, glm::vec3(0.f, 0.f, 0.f)), x_values(w,0), y_values(h,0) {
    this->m_display.create(sf::VideoMode(w, h), text);
    this->m_buffer.create(w, h);

    if (!this->m_font.loadFromFile("./bin/fonts/pixelmix.ttf")) {
        std::cerr << ":) no font" << std::endl;
    }

    this->m_fpsText.setFont(this->m_font);
    this->m_fpsText.setCharacterSize(24);
    this->m_fpsText.setFillColor(sf::Color(0xff00ffff));
    this->m_fpsText.setPosition(10.f, 10.f);

    //this->m_display.setFramerateLimit(this->m_fpsLimit);
    
    std::iota(y_values.begin(), y_values.end(), 0); 
    std::iota(x_values.begin(), x_values.end(), 0);
}

void Window::repaint(float& dt, Camera& cam, Scene& scn, sf::Event& ev) {
    this->m_fps = static_cast<uint16_t>(1.f / dt);
    this->m_fpsText.setString("FPS: " + std::to_string(this->m_fps));
    
    glm::ivec2 buff_v(this->m_buffer.getSize().x, this->m_buffer.getSize().y);

    bool resetAccumulation = false;
    if (ev.type == sf::Event::KeyPressed) {
        resetAccumulation = true;
        if (ev.key.code == sf::Keyboard::Tab) {
            this->m_buffer.saveToFile("./bin/screenshot.jpg");
        }
    }

    if (resetAccumulation) {
        this->m_frames = 0;
        this->m_acumulation = std::vector<glm::vec3>(buff_v.x * buff_v.y, glm::vec3(0.f, 0.f, 0.f));
    }
    this->m_frames += 1;

    sf::Color lastCol;
    std::for_each(std::execution::par, y_values.begin(), y_values.end(), [&](int y) {
        std::for_each(std::execution::par, x_values.begin(), x_values.end(), [&](int x) {
            const int index = buff_v.x * y + x;
            sf::Color col = shader(x, y, buff_v, cam, scn, lastCol);
            sf::Color fcolor;

            //acumulation
            this->m_acumulation[index] += glm::vec3(col.r, col.g, col.b);

            fcolor = sf::Color(
                    this->m_acumulation[index].r/this->m_frames, 
                    this->m_acumulation[index].g/this->m_frames, 
                    this->m_acumulation[index].b/this->m_frames);
#if ANTIALIASING            
            this->m_buffer.setPixel(x, y, fcolor);
            
            // antialiasing
            if (x < 1 || x > buff_v.x-1 || y < 1 || y > buff_v.y-1) {
                return;
            }

            float r = 0.f, g = 0.f, b = 0.f;
            for (int offx = -1; offx <= 1; offx += 1) {
                for (int offy = -1; offy <= 1; offy += 1) {
                    if(offx == 0 && offy == 0) {
                        r += this->m_buffer.getPixel(x + offx, y + offy).r * 2; 
                        g += this->m_buffer.getPixel(x + offx, y + offy).g * 2; 
                        b += this->m_buffer.getPixel(x + offx, y + offy).b * 2;
                    } else {
                        r += this->m_buffer.getPixel(x + offx, y + offy).r; 
                        g += this->m_buffer.getPixel(x + offx, y + offy).g; 
                        b += this->m_buffer.getPixel(x + offx, y + offy).b;
                    } 
                }
            }
            r /= 10.0f;
            g /= 10.0f;
            b /= 10.0f;
            fcolor = sf::Color(static_cast<sf::Uint8>(r), 
                               static_cast<sf::Uint8>(g), 
                               static_cast<sf::Uint8>(b));
#endif            
            this->m_buffer.setPixel(x, y, resetAccumulation ? col : fcolor);
        });
    });

    this->m_texture.loadFromImage(this->m_buffer);
    this->m_sprite.setTexture(this->m_texture);
    float scale = static_cast<float>(this->m_display.getSize().x) / buff_v.x;
    this->m_sprite.setScale(scale, scale);

    this->m_display.clear(); 

    this->m_display.draw(this->m_sprite);
    this->m_display.draw(this->m_fpsText);

    sf::CircleShape camera;
    camera.setPosition(cam.position().x+this->m_display.getSize().x/2,
            cam.position().z+this->m_display.getSize().y/2);
    camera.setFillColor(sf::Color(255, 255, 0));
    camera.setRadius(10);
    this->m_display.draw(camera);

    for (int i = 0; i < scn.triangle().size()+scn.sphere().size()-1; i++) {
        sf::CircleShape plane;
        plane.setPosition(scn.object(i).center.x+this->m_display.getSize().x/2, 
                scn.object(i).center.z+this->m_display.getSize().y/2);
        plane.setFillColor(sf::Color(255,0,255));
        plane.setRadius(10);

        this->m_display.draw(plane);
    }

    this->m_display.display();

    if (ev.key.code == sf::Keyboard::Tab) {
        this->m_buffer.saveToFile("./bin/screenshot.jpg");
    }
}
