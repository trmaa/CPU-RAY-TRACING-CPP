#include "./window.hpp"
#include "./camera.hpp"
#include "./scene.hpp"
#include <glm/ext/vector_int2.hpp>

sf::Color shader(int* x, int* y, glm::ivec2* buff_v, Camera* cam, Scene* scn, sf::Color* lastCol) 
{

const int index = *x + *y * buff_v->x;

sf::Color col(0x000000ff);
Ray* ray = cam->ray(index);
cam->cast(x, y, buff_v);

int bounces = 10;
for (int i = 0; i < bounces; i++) { 
	std::vector<float> times;
	for (int j = 0; j < scn->sphere()->size(); j++) {
		times.push_back(scn->sphere(j)->checkCollision(ray));
	}
	auto t = std::min_element(times.begin(), times.end(), [](float a, float b){
		return std::abs(a) < std::abs(b); 
	}); //t is a pointer
	int id = std::distance(times.begin(), t);
	Sphere* sphere = scn->sphere(id);

	if (*t <= 0) {
		if (i < 1) {
			col = sf::Color(
				255*(1+cam->direction()->x)*0.5f,
				255*(1+cam->direction()->y)*0.5f,
				255*(1+cam->direction()->z)*0.5f,
				255
			);
			return col;
		}
		col = *lastCol;
		return col;
	}

	col = *sphere->material.col();
	 
	glm::vec3 hitPoint = ray->f(*t);
	glm::vec3 normal = glm::normalize(hitPoint - sphere->center);

	glm::vec3 incoming_direction = glm::normalize(ray->direction);
	glm::vec3 reflected_direction = incoming_direction - 2.0f * glm::dot(incoming_direction, normal) + normal;

	ray->origin = hitPoint + normal;
	ray->direction = reflected_direction;

	/*col = sf::Color(
		255*(1+normal.x)*0.5f,
		255*(1+normal.y)*0.5f,
		255*(1+normal.z)*0.5f,
		255
	);*/
	
	*lastCol = col;
}    
return col;

}
