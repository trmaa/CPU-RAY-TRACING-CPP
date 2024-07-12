#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>
#include <cmath>

struct Material {
    glm::vec3 color;
    float emission;
    float roughness;
    sf::Image texture;

    Material(glm::vec3 c, float e, float r, const std::string& txtrPath): color(c), emission(e), roughness(r) {
        if (!texture.loadFromFile(txtrPath)) {
            texture.create(1,1);
            texture.setPixel(0, 0, sf::Color(c.r, c.g, c.b));
        }
    }

    ~Material() = default;

    const sf::Color col() const { 
        return sf::Color(static_cast<sf::Uint8>(this->color.r * 255), static_cast<sf::Uint8>(this->color.g * 255), static_cast<sf::Uint8>(this->color.b * 255)); 
    }

    const sf::Color txtr(const glm::vec3 normal) const {
        float theta = std::acos(normal.y);
        float phi = std::atan2(normal.z, normal.x);

        float u = (phi + M_PI) / (2 * M_PI);
        float v = theta / M_PI;

        int texWidth = texture.getSize().x;
        int texHeight = texture.getSize().y;
        int x = static_cast<int>(u * texWidth) % texWidth;
        int y = static_cast<int>((texHeight - v) * texHeight) % texHeight;

        sf::Color color = texture.getPixel(x, y);
        return sf::Color(color.r*this->color.r/255.f, color.g*this->color.g/255.f, color.b*this->color.b/255.f);
    }
};

#endif
