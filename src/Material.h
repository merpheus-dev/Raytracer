#pragma once
#include <glm.hpp>
class Material
{
public:
	Material(glm::vec3 albedo, glm::vec3 specular, float specular_power,float reflectivity)
					:diffuse(albedo), specular_color(specular), specular_power(specular_power),reflectivity(reflectivity) {  }
	
	glm::vec3 diffuse;
	glm::vec3 specular_color;
	//High specPow will produce sharper gloss distribution, smaller values will have smoother bigger transitions
	float specular_power;
	float reflectivity;
};