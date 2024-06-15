#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <glm/glm.hpp>
#include <string>
#include "./sphere.hpp"
#include "./camera.hpp"

class Window {
private:
    glm::ivec2 m_viewport;
    sf::Image m_buffer;
    sf::RenderWindow m_display;

    sf::Font m_font;
    sf::Text m_fpsText;
    uint16_t m_fps;
    uint8_t m_fpsLimit = 40;

    sf::Texture m_texture;  
    sf::Sprite m_sprite;
public:
    sf::Image* buffer() { return &this->m_buffer; }
    sf::RenderWindow* display() { return &this->m_display; }

    Window(int w, int h, std::string text): m_viewport(w, h) {
        this->m_display.create(sf::VideoMode(w, h), text);
        this->m_buffer.create(w, h);

        if (!this->m_font.loadFromFile("./fonts/pixelmix.ttf")) {
            std::cerr << ":) no font" << std::endl;
        }

        this->m_fpsText.setFont(this->m_font);
        this->m_fpsText.setCharacterSize(24);
        this->m_fpsText.setFillColor(sf::Color(0xff00ffff));
        this->m_fpsText.setPosition(10.f, 10.f);

        this->m_display.setFramerateLimit(this->m_fpsLimit);
    }
    ~Window() = default;
public:
    void repaint(float *dt, Camera *cam) {
        this->m_fps = static_cast<uint16_t>(1.f / *dt);
        this->m_fpsText.setString("FPS: " + std::to_string(this->m_fps));
        
        glm::ivec2 buff_v(this->m_buffer.getSize().x, this->m_buffer.getSize().y);
        for (int y = 0; y < buff_v.y; y++) {
            for (int x = 0; x < buff_v.x; x++) {
                int index = x+y*buff_v.x;

                sf::Color col(
                    x * 255 / buff_v.x, 
                    y * 255 / buff_v.y, 0);
                
                /* specular and just spheres
                
                void shader():
                    for *rays:
                        for nbounces:
                            for *objects from the json scene:
                                if object ->check colission (ray):
                                    collided local objects .push (object)
                                    times .push (time)
                            lower time = sort (times)
                            index = times .idAt (lower time)
                            
                            if lower time < 0:
                                if bounc == 0:
                                    color = SKY COLOR
                                else:
                                    color = LAST COLOR
                                continue;
                        
                            color, LAST COLOR = objects[index]->color*SKY COLOR

                            ray.origin = ray.f(lower time)
                            ray.direction = normal(ray.origin - object.center)

                */
                Sphere sphere(glm::vec3(0,0,20), 15);
                cam->cast(index);
                int coll = sphere.checkColission(cam->ray(index));
                if(coll){
                    col = sf::Color(255,255,255);
                }

                this->m_buffer.setPixel(x, y, col);
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
};

#endif
