#include<SFML/Graphics.hpp>
#include<cstdlib>
#include<iostream>
#include<glm/glm.hpp>
#include"../includes/window.hpp"

sf::RenderWindow Window::window;
sf::Image Window::m_buffer;

sf::Font Window::m_font;
sf::Text Window::m_fpsText;

void Window::repaint(float dt){
    float fps = 1.f/dt;
    Window::m_fpsText.setString("FPS: " + std::to_string(static_cast<int>(fps)));

    for(unsigned int y = 0; y < m_buffer.getSize().y; ++y){
        for(unsigned int x = 0; x < m_buffer.getSize().x; ++x){
            sf::Color col(x*255/Window::m_buffer.getSize().x, y*255/Window::m_buffer.getSize().y,0);
            m_buffer.setPixel(x, y, col);
        }
    }

    sf::Texture texture;
    texture.loadFromImage(m_buffer);

    sf::Sprite sprite(texture);

    window.clear();
    window.draw(sprite);
    window.draw(m_fpsText);
    window.display();
}

void Window::open(){
    Window::window.create(sf::VideoMode(1280, 720), "SFML works!");
    Window::m_buffer.create(1280,720);
    
    if(!Window::m_font.loadFromFile("./fonts/pixelmix.ttf")) {
        std::cerr<<"There is no font";
    }

    Window::m_fpsText.setFont(Window::m_font);
    Window::m_fpsText.setCharacterSize(24);
    Window::m_fpsText.setFillColor(sf::Color::White);
    Window::m_fpsText.setPosition(10.f, 10.f);
}
