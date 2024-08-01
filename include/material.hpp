#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <glm/detail/qualifier.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/geometric.hpp>
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
        float theta = std::acos(-normal.y);
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

    sf::Color txtr(glm::vec3 hitp, glm::vec3 center, glm::vec3 normal) const {
        // Define the plane dimensions
        float planeWidth = 100.0f;
        float planeHeight = 100.0f;

        // Calculate the tangent and bitangent vectors
        glm::vec3 tangent, bitangent;
        if (fabs(normal.x) > fabs(normal.y)) {
            tangent = glm::vec3(normal.z, 0, -normal.x);
        } else {
            tangent = glm::vec3(0, -normal.z, normal.y);
        }
        tangent = glm::normalize(tangent);
        bitangent = glm::normalize(glm::cross(normal, tangent));

        // Calculate the local coordinates of the hit point relative to the plane center
        glm::vec3 localHitPoint = hitp - center;
        float u = glm::dot(localHitPoint, tangent) / planeWidth;
        float v = glm::dot(localHitPoint, bitangent) / planeHeight;

        // Map the local coordinates to texture coordinates
        // Assuming the texture repeats and its dimensions are texture.getSize().x by texture.getSize().y
        u = fmod(u, 1.0f);
        v = fmod(v, 1.0f);
        if (u < 0) u += 1.0f;
        if (v < 0) v += 1.0f;

        // Scale texture coordinates to the image size
        unsigned int texWidth = texture.getSize().x;
        unsigned int texHeight = texture.getSize().y;
        unsigned int texX = static_cast<unsigned int>(u * texWidth);
        unsigned int texY = static_cast<unsigned int>(v * texHeight);

        // Get the color from the texture
        return texture.getPixel(texX, texY);
    }
};

#endif
