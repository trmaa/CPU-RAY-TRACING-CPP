#ifndef WINDOW_HPP
#define WINDOW_HPP

#define ANTIALIASING 0
#define MAP 0

#include "camera.hpp"
#include "scene.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <glm/ext/vector_int2.hpp>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <algorithm>
#include <execution>

sf::Color shader(int& x, int& y, glm::ivec2& buff_v, Camera& cam, Scene& scn, sf::Color& lastCol);

class Window: public sf::RenderWindow {
private:
    glm::ivec2 m_viewport;
    sf::Image m_buffer;
    int m_frames;
    std::vector<glm::vec3> m_acumulation;

    sf::Font m_font;
    sf::Text m_fpsText;
    uint16_t m_fps;
    uint8_t m_fpsLimit = 45;

    sf::Texture m_texture;  
    sf::Sprite m_sprite;
    
    std::vector<int> x_values;
    std::vector<int> y_values;

public:
    const sf::Image& buffer() { return this->m_buffer; }
    
    Window(const int& w, const int& h, std::string text)
        : m_viewport(w, h), m_frames(0), m_acumulation(w * h, glm::vec3(0.f, 0.f, 0.f)), x_values(w,0), y_values(h,0) {
        this->create(sf::VideoMode(w, h), text);
        this->m_buffer.create(w, h);

        if (!this->m_font.loadFromFile("./bin/fonts/pixelmix.ttf")) {
            std::cerr << ":) no font" << std::endl;
        }

        this->m_fpsText.setFont(this->m_font);
        this->m_fpsText.setCharacterSize(24);
        this->m_fpsText.setFillColor(sf::Color(0xff00ffff));
        this->m_fpsText.setPosition(10.f, 10.f);

        this->setFramerateLimit(this->m_fpsLimit);
        
        std::iota(y_values.begin(), y_values.end(), 0); 
        std::iota(x_values.begin(), x_values.end(), 0);
    }
    ~Window() = default;

public:
    void repaint(float& dt, Camera& cam, Scene& scn, sf::Event& ev) {
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
        float scale = static_cast<float>(this->getSize().x) / buff_v.x;
        this->m_sprite.setScale(scale, scale);

        this->clear(); 

        this->draw(this->m_sprite);
        this->draw(this->m_fpsText);

#if MAP
        sf::CircleShape camera;
        camera.setPosition(0.1f*cam.position().x+this->getSize().x/2,
                0.1f*cam.position().z+this->getSize().y/2);
        camera.setFillColor(sf::Color(255, 255, 0));
        camera.setRadius(10);
        this->draw(camera);

        for (int i = 0; i < scn.triangle().size()+scn.sphere().size()-1; i++) {
            sf::CircleShape plane;
            plane.setPosition(0.1f*scn.object(i).center.x+this->getSize().x/2, 
                    0.1f*scn.object(i).center.z+this->getSize().y/2);
            plane.setFillColor(sf::Color(255,0,255));
            plane.setRadius(10);

            this->draw(plane);
        }
#endif

        this->display();

        if (ev.key.code == sf::Keyboard::Tab) {
            this->m_buffer.saveToFile("./bin/screenshot.jpg");
        }
    }
};

#endif
