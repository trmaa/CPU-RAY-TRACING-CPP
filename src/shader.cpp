#include "./window.hpp"
#include "./random.hpp"
#include "./camera.hpp"
#include "./scene.hpp"
#include <SFML/Graphics/Color.hpp>
#include <glm/detail/qualifier.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_int2.hpp>

sf::Color shader(int* x, int* y, glm::ivec2* buff_v, Camera* cam, Scene* scn, sf::Color* lastCol) 
{
    const int index = *x + *y * buff_v->x;

    glm::vec3 sc = *scn->sky_color();
    sf::Color col = sf::Color(sc.r * 255, sc.g * 255, sc.b * 255);
    Ray* ray = &cam->ray[index];
    cam->cast(x, y, buff_v);

    int bounces = 10;
    for (int i = 0; i < bounces; i++) {
        float importance = static_cast<float>(bounces - i) / bounces;

        std::vector<float> times;
        for (int j = 0; j < scn->sphere()->size(); j++) {
            times.push_back(scn->sphere(j)->checkCollision(ray));
        }
        auto t = std::min_element(times.begin(), times.end(), [](float a, float b) {
            return std::abs(a) < std::abs(b); 
        }); // t is a pointer
        int id = std::distance(times.begin(), t);
        const Sphere* sphere = scn->sphere(id);

        if (*t <= 0) {
            if (i < 1) {
                return col;
            }
            sf::Color lc = *lastCol;
            glm::vec3 nc = sc * glm::vec3(lc.r, lc.g, lc.b) * importance;
            col = sf::Color(nc.r, nc.g, nc.b);
            return col;
        }

        glm::vec3 color = sphere->material.color * importance;
        col = sf::Color(color.r, color.g, color.b);

        if (sphere->material.emission > 0) {
            if (i < 1) {
                glm::vec3 nc = sphere->material.emission * sphere->material.color;
                col = sf::Color(nc.r, nc.g, nc.b);
                return col;
            }
            sf::Color lc = *lastCol;
            glm::vec3 nc = glm::vec3(lc.r, lc.g, lc.b) * sphere->material.color / 255.f;
            col = sf::Color(nc.r, nc.g, nc.b);
            return col;
        }

        glm::vec3 hitPoint = ray->f(*t);
        glm::vec3 normal = glm::normalize(hitPoint - sphere->center);

        glm::vec3 reflected_direction = ray->direction - 2.0f * glm::dot(ray->direction, normal) * normal;

        glm::vec3 diffusion(0);
        if (sphere->material.roughness > 0) {
            diffusion = glm::normalize(
                    glm::vec3(random_float(), random_float(), random_float()) 
                    * 2.0f - glm::vec3(1.0f)) * sphere->material.roughness;
        }

        *ray = Ray(hitPoint + normal * 0.001f, (reflected_direction + diffusion));

        *lastCol = col;
    }    
    return col;
}
