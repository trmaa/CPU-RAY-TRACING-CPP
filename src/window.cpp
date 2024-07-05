#include "window.hpp"
#include <SFML/Graphics/Color.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_int2.hpp>
#include <iostream>

Window::Window(int w, int h, std::string text)
    : m_viewport(w, h), m_frames(0), m_acumulation(w * h, glm::vec3(0.f, 0.f, 0.f)) {
    this->m_display.create(sf::VideoMode(w, h), text);
    this->m_buffer.create(w, h);

    if (!this->m_font.loadFromFile("./fonts/pixelmix.ttf")) {
        std::cerr << ":) no font" << std::endl;
    }

    this->m_fpsText.setFont(this->m_font);
    this->m_fpsText.setCharacterSize(24);
    this->m_fpsText.setFillColor(sf::Color(0xff00ffff));
    this->m_fpsText.setPosition(10.f, 10.f);

    //this->m_display.setFramerateLimit(this->m_fpsLimit);
}

void Window::repaint(float* dt, Camera* cam, Scene* scn, sf::Event* ev) {
    this->m_fps = static_cast<uint16_t>(1.f / *dt);
    this->m_fpsText.setString("FPS: " + std::to_string(this->m_fps));
    
    glm::ivec2 buff_v(this->m_buffer.getSize().x, this->m_buffer.getSize().y);

    bool resetAccumulation = false;
    if (ev->type == sf::Event::KeyPressed) {
        resetAccumulation = true;
        if (ev->key.code == sf::Keyboard::Tab) {
            this->m_buffer.saveToFile("./bin/screenshot.jpg");
        }
    }

    if (resetAccumulation) {
        this->m_frames = 0;
        this->m_acumulation = std::vector<glm::vec3>(buff_v.x * buff_v.y, glm::vec3(0.f, 0.f, 0.f));
    }
    this->m_frames += 1;

    sf::Color lastCol;
    for (int y = 0; y < buff_v.y; y++) {
        for (int x = 0; x < buff_v.x; x++) {
            const int index = buff_v.x * y + x;
            sf::Color col = shader(&x, &y, &buff_v, cam, scn, &lastCol);
            sf::Color fcolor;

            //acumulation
            this->m_acumulation[index] = (
                    this->m_acumulation[index] * static_cast<float>(this->m_frames) 
                    + glm::vec3(col.r, col.g, col.b)) / static_cast<float>(this->m_frames + 1);

            fcolor = sf::Color(
                    this->m_acumulation[index].r, 
                    this->m_acumulation[index].g, 
                    this->m_acumulation[index].b);
            
            /*this->m_buffer.setPixel(x, y, fcolor);
            
            // antialiasing
            if (x < 1 || x > buff_v.x-1 || y < 1 || y > buff_v.y-1) {
                continue;
            }

            float r = 0.f, g = 0.f, b = 0.f;
            for (int offx = -1; offx <= 1; offx++) {
                for (int offy = -1; offy <= 1; offy++) {
                    r += this->m_buffer.getPixel(x + offx, y + offy).r; 
                    g += this->m_buffer.getPixel(x + offx, y + offy).g; 
                    b += this->m_buffer.getPixel(x + offx, y + offy).b; 
                }
            }
            r /= 9.0f;
            g /= 9.0f;
            b /= 9.0f;
            fcolor = sf::Color(static_cast<sf::Uint8>(r), 
                               static_cast<sf::Uint8>(g), 
                               static_cast<sf::Uint8>(b));
            */   
            this->m_buffer.setPixel(x, y, resetAccumulation ? col : fcolor);   
        }
    }

    this->m_texture.loadFromImage(this->m_buffer);
    this->m_sprite.setTexture(this->m_texture);
    float scale = static_cast<float>(this->m_display.getSize().x) / buff_v.x;
    this->m_sprite.setScale(scale, scale);

    this->m_display.clear();
    this->m_display.draw(this->m_sprite);
    this->m_display.draw(this->m_fpsText);
    this->m_display.display();
}
