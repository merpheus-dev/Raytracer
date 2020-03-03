#pragma once
#include <glm.hpp>
class Material
{
public:
	Material(glm::vec3 color):diffuse(color) {  }
	glm::vec3 diffuse;
};