#pragma once
#include <glm.hpp>
#include "Material.h"
class Sphere
{
public:
	Sphere(glm::vec3 center, float radius,Material* material) : _center(center), _radius(radius),material(material) {}
	bool ray_intersect(glm::vec3 rayOrigin, glm::vec3 rayDirection, float& nearestIntersection);
	glm::vec3 _center;
	float _radius;
	Material* material;
};