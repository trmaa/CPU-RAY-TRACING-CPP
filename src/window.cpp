#include "window.hpp"

Window::Window(int w, int h, std::string text): m_viewport(w, h) {
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

void Window::repaint(float *dt, Camera *cam, Scene *scn, sf::Event* ev) {
    this->m_fps = static_cast<uint16_t>(1.f / *dt);
    this->m_fpsText.setString("FPS: " + std::to_string(this->m_fps));
    
    glm::ivec2* buff_v = new glm::ivec2(this->m_buffer.getSize().x, this->m_buffer.getSize().y);

    sf::Color lastCol;
    for (int y = 0; y < buff_v->y; y++) {
        for (int x = 0; x < buff_v->x; x++) {
            sf::Color col = shader(&x, &y, buff_v, cam, scn, &lastCol);
            this->m_buffer.setPixel(x, y, col);
        }
    }

    this->m_texture.loadFromImage(this->m_buffer);
    this->m_sprite.setTexture(this->m_texture);
    float scale = static_cast<float>(this->m_display.getSize().x) / buff_v->x;
    this->m_sprite.setScale(scale, scale);

    this->m_display.clear();
    this->m_display.draw(this->m_sprite);
    this->m_display.draw(this->m_fpsText);
    this->m_display.display();

    if (ev->key.code == sf::Keyboard::Tab) {
        this->m_buffer.saveToFile("./bin/screenshot.jpg");
    }

    delete buff_v;
}
