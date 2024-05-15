#include "camera.hpp"
#include "window.hpp"

std::vector<glm::vec2> Camera::ray;

void Camera::start(){                                 
    for(int y = 0; y < Window::viewport.y; y++){
        for(int x = 0; x < Window::viewport.x; x++){
            Camera::ray.push_back(glm::vec2(x, y));
        }
    }                                   
}
