#ifndef SCENE_HPP
#define SCENE_HPP

#include "./json.hpp"
#include "./sphere.hpp"
#include <fstream>
#include <future>
#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <vector>

class Scene {
private:
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
	std::vector<Sphere>* sphere() { return &this->m_sphere; }
	Sphere* sphere(const int index) { return &this->m_sphere[index]; }

	Scene(const std::string& fpath) {
		std::future<nl::json> raw = std::async(std::launch::async, Scene::readJson, fpath);
		nl::json data = raw.get();
		if (!data.contains("sphere"))
			return;
		for (const auto& obj : data["sphere"]) {
			glm::vec3 center(obj["center"][0], obj["center"][1], obj["center"][2]);
			float radius = obj["radius"];
			glm::vec3 color(obj["color"][0], obj["color"][1], obj["color"][2]);
			this->m_sphere.emplace_back(center, radius, color);
		}
	}
	~Scene() = default;
};

#endif
