#pragma once
#include <glm.hpp>
class Material
{
public:
	Material(glm::vec3 albedo, glm::vec3 specular, float specular_power,float reflectivity,float metallic)
					:diffuse(albedo), specular_color(specular), specular_power(specular_power),reflectivity(reflectivity),metallic(metallic) {  }
	
	glm::vec3 diffuse;
	glm::vec3 specular_color;
	float diffuse_multiplier = 1;
	float specular_multiplier = 1;
	//High specPow will produce sharper gloss distribution, smaller values will have smoother bigger transitions
	float specular_power;
	float reflectivity;
	float metallic = 0;
};