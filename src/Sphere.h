#pragma once
#include <glm.hpp>
class Sphere
{
public:
	Sphere(glm::vec3 center, float radius) : _center(center), _radius(radius) {}
	bool ray_intersect(glm::vec3 rayOrigin, glm::vec3 rayDirection);
	glm::vec3 _center;
	float _radius;
};