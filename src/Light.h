#pragma once
#include <glm.hpp>
class Light
{
public:
	Light(const glm::vec3& position,const float& intensity) :position(position),intensity(intensity) {  }
	glm::vec3 position;
	float intensity;
};