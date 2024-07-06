#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <glm/ext/vector_int2.hpp>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "./camera.hpp"
#include "./scene.hpp"

sf::Color shader(int* x, int* y, glm::ivec2* buff_v, Camera* cam, Scene* scn, sf::Color* lastCol);

class Window {
private:
    glm::ivec2 m_viewport;
    sf::Image m_buffer;
    int m_frames;
    std::vector<glm::vec3> m_acumulation;
    sf::RenderWindow m_display;

    sf::Font m_font;
    sf::Text m_fpsText;
    uint16_t m_fps;
    uint8_t m_fpsLimit = 15;

    sf::Texture m_texture;  
    sf::Sprite m_sprite;
    
    std::vector<int> x_values;
    std::vector<int> y_values;

public:
    sf::Image* buffer() { return &this->m_buffer; }
    sf::RenderWindow* display() { return &this->m_display; }

    Window(int w, int h, std::string text);
    ~Window() = default;

public:
    void repaint(float *dt, Camera *cam, Scene *scn, sf::Event* ev);
};

#endif
