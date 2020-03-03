#include "Sphere.h"
#include <iostream>

bool Sphere::ray_intersect(glm::vec3 rayOrigin, glm::vec3 rayDirection,float& nearestIntersection)
{
	glm::vec3 oc_vector = _center - rayOrigin;
	float dp = glm::dot(oc_vector, rayDirection);
	glm::vec3 p = rayOrigin + rayDirection * dp;
	float y = glm::length(_center - p);
	if (y > _radius) return false;
	float x = glm::sqrt(_radius * _radius - y * y);
	float p1 = dp + x; //distance relative to ray origin
	float p2 = dp - x;
	if (p1 < 0 || p2 < 0) return false; //so if those points are behind, this means sphere can not be rendered
	if (p1 > 0 && p1 >= p2) nearestIntersection = p1;
	else if (p2 > 0 && p2 >= p1) nearestIntersection = p2;
	return true;
}
