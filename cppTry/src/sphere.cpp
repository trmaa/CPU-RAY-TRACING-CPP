#include "sphere.hpp"
#include "ray.hpp"
#include "camera.hpp"

glm::vec3 Sphere::possition(0,0,30);
float Sphere::radius = 10;

float Sphere::collission(Ray ray) {
	glm::vec3 oc = Camera::possition - Sphere::possition;
                                    
    float a = glm::dot(ray.direction(), ray.direction());
    float b = glm::dot(oc, ray.direction()+ray.direction());
    float c = glm::dot(oc,oc) - Sphere::radius * Sphere::radius;
                                    
    float discriminant = b * b - 4 * a * c;

    return (discriminant < 0) ? 0 : (-(float)std::sqrt(discriminant) - b) / (2 * a);
}
