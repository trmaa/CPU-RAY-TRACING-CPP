#include <stdio.h>
#include <cmath>
#include "camera.hpp"
#include "window.hpp"
#include "ray.hpp"

glm::vec3 Camera::possition(0,0,0);
glm::vec3 Camera::angle(0,3.14,0);
std::vector<Ray> Camera::ray;

void Camera::start(){                                 
    for(int y = 0; y < Window::viewport.y; y++){
        for(int x = 0; x < Window::viewport.x; x++){
            Camera::ray.push_back(Ray(Camera::possition,glm::vec3(x,y,0)));
        }
    }
}

void Camera::cast(Ray* ray){
	ray.orig = Camera::possition;
	ray.dir = glm::vec3(
		ray.dir.x*(float)std::cos(Camera::angle.y)*(float)std::cos(Camera::angle.x),
		ray.dir.y*(float)std::sin(Camera::angle.x),
		ray.dir.z*(float)std::sin(Camera::angle.y)*(float)std::cos(Camera::angle.x)
	);
}
