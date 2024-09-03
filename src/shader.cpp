#include "window.hpp"
#include "random.hpp"
#include "camera.hpp"
#include "scene.hpp"
#include "object.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <algorithm>
#include <cstdio>
#include <glm/detail/qualifier.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_int2.hpp>
#include <glm/geometric.hpp>
#include <vector>

sf::Color shader(int& x, int& y, glm::ivec2& buff_v, Camera& cam, Scene& scn, sf::Color& lastCol) 
{

const int index = x + y * buff_v.x;

glm::vec3 sc = scn.sky_color();
sf::Color col = sf::Color(sc.r * 255, sc.g * 255, sc.b * 255);
Ray ray = cam.ray[index];
cam.cast(x, y, buff_v);

int bounces = 4;
for (int i = 0; i < bounces; i++) {
    float importance = static_cast<float>(bounces - i*(1)) / bounces;
    importance = importance<0?0:importance;

    std::vector<float> times;
    for (int j = 0; j < scn.sphere().size()+scn.triangle().size(); j++) {
        times.push_back(scn.object(j).checkCollision(ray));
    }
    auto t = std::min_element(times.begin(), times.end(), [](float a, float b) {
        return std::abs(a) < std::abs(b); 
    }); // t is a pointer
    int id = std::distance(times.begin(), t);
    const Object& object = scn.object(id);

    if (*t < 0) {
        if (i < 1) {
            lastCol = col;
            return col;
        }
        sf::Color lc = lastCol;
        glm::vec3 nc = sc * glm::vec3(lc.r, lc.g, lc.b);
        lastCol = sf::Color(nc.r, nc.g, nc.b);
        nc *= importance;
        lastCol = sf::Color(nc.r, nc.g, nc.b);
        col = sf::Color(nc.r, nc.g, nc.b);
        return col;
    }

    glm::vec3 hitPoint = ray.f(*t);
    
    glm::vec3 normal;
    if (object.type() == "Triangle") {
        normal = object.normal;
    } else {
        normal = glm::normalize(object.center-hitPoint);
    }
    if (glm::dot(ray.direction, normal) > 3.14159f/2) {	
        normal = normal*(-1.f);
	}

    if (object.material.emission > 0) {
        sf::Color tc = object.type()=="Triangle"?object.material.txtr(ray.f(*t), object.center, normal):object.material.txtr(normal);
        if (i < 1) {
            glm::vec3 nc = object.material.emission*glm::vec3(tc.r, tc.g, tc.b);
            col = sf::Color(nc.r, nc.g, nc.b);
            lastCol = col;
            return col;
        }
        sf::Color lc = lastCol;
        glm::vec3 nc = glm::normalize(glm::vec3(lc.r, lc.g, lc.b))
            *glm::vec3(tc.r, tc.g, tc.b)*object.material.emission;
        col = sf::Color(nc.r, nc.g, nc.b);
        lastCol = col;
        return col;
    }

    sf::Color tC = object.type()=="Triangle"?object.material.txtr(ray.f(*t), object.center, normal):object.material.txtr(normal);
    if (i < 1) {
        lastCol = tC;
    } else {    
        glm::vec3 lc = glm::vec3(lastCol.r, lastCol.g, lastCol.b) * glm::normalize(glm::vec3(tC.r, tC.g, tC.b));
        lastCol = sf::Color(lc.r, lc.g, lc.b);
    }
    glm::vec3 color = glm::vec3(lastCol.r, lastCol.g, lastCol.b) * glm::normalize(glm::vec3(tC.r, tC.g, tC.b) * importance);
    col = sf::Color(color.r, color.g, color.b);

    glm::vec3 reflected_direction = ray.direction - 2.0f * glm::dot(ray.direction, normal) * normal;

    glm::vec3 diffusion(0);
    if (object.material.roughness > 0) {
        diffusion = glm::normalize(
                glm::vec3(rando_float(), rando_float(), rando_float()) 
                * 2.0f - glm::vec3(1.0f)) * object.material.roughness;
    }

    ray = Ray(hitPoint + normal * 0.001f, (reflected_direction + diffusion));
}
return col;

}
