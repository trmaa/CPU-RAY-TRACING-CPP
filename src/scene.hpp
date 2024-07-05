#ifndef SCENE_HPP
#define SCENE_HPP

#include "./json.hpp"
#include "./sphere.hpp"
#include <fstream>
#include <future>
#include <glm/ext/vector_float3.hpp>
#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <vector>

class Scene {
private:
	glm::vec3 m_sky_color;
	std::vector<Sphere> m_sphere;
private:
	static nl::json readJson(const std::string& fpath) {
		std::ifstream file(fpath);
		if (!file.is_open()) {
			std::cerr<<"Json corrupt"<<std::endl;
			return "";
		}
		nl::json data;
		file >> data;
		return data;
	}
public:
	const std::vector<Sphere>* sphere() const { return &this->m_sphere; }
	const Sphere* sphere(const int index) const { return &this->m_sphere[index]; }

	glm::vec3* sky_color() { return &this->m_sky_color; }
	
	Scene(const std::string& fpath) {
		std::future<nl::json> raw = std::async(std::launch::async, Scene::readJson, fpath);
		nl::json data = raw.get();
		if (!data.contains("sphere") || !data.contains("sky"))
			return;
		for (const auto& obj : data["sphere"]) {
			glm::vec3 center(obj["center"][0], obj["center"][1], obj["center"][2]);
			float radius = obj["radius"];
			glm::vec3 color(obj["color"][0], obj["color"][1], obj["color"][2]);
			float emission = obj["emission"];
			float roughness = static_cast<float>(obj["roughness"]);
			std::string path = obj["texture"];
			this->m_sphere.emplace_back(center, radius, color, emission, roughness, path);
		}
		this->m_sky_color = glm::vec3(data["sky"][0],data["sky"][1],data["sky"][2]);
	}
	~Scene() = default;
};

#endif
