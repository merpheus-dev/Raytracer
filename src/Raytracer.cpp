#include "Raytracer.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <fstream>
#include <limits>
#include <algorithm>

void Raytracer::render()
{
	fill_frame_buffer();
	write_image_to_disk();
}

void Raytracer::set_render_targets(std::vector<Sphere*>& spheres)
{
	this->spheres = spheres;
}

void Raytracer::set_lights(std::vector<Light*>& lights)
{
	this->lights = lights;
}

void Raytracer::fill_frame_buffer()
{
	auto aspectRatio = width / float(height);
	for (size_t j = 0; j < height; j++)
	{
		for (size_t i = 0; i < width; i++)
		{
			///(2 * (currentPixel * middle_of_pixel_cord) / float(width) + z_depth_by_direction)
			const auto x = (2 * (i * .5f) / float(width) - 1) * glm::tan(fov / 2.f) * aspectRatio;
			const auto y = -(2 * (j * .5f) / float(height) - 1) * glm::tan(fov / 2.f);
			glm::vec3 rayDir = glm::normalize(glm::vec3(x, y, 1));
			frame_buffer_[i + j * width] = cast_ray(glm::vec3(0), rayDir);
		}
	}
}

void Raytracer::push_to_pixel_buffer()
{
	pixels = new uint8_t[width * height * 3];

	auto index = 0;
	for (auto j = 0; j < height; j++)
	{
		for (auto i = 0; i < width; ++i)
		{
			auto target_pixel = frame_buffer_[i + j * width];
			//Clamp pixel color to 1
			const float max_color_value = std::max(target_pixel.r, std::max(target_pixel.g, target_pixel.b));
			if (max_color_value > 1.f) target_pixel /= max_color_value;
			pixels[index++] = int(255.99 * target_pixel.r);
			pixels[index++] = int(255.99 * target_pixel.g);
			pixels[index++] = int(255.99 * target_pixel.b);
		}
	}
}

void Raytracer::write_image_to_disk()
{
	push_to_pixel_buffer();
	stbi_write_jpg("test.jpg", width, height, 3, pixels, 100);
}

glm::vec3 Raytracer::cast_ray(const glm::vec3& rayOrigin, const glm::vec3 rayDirection)
{
	float zDistance = farPlane;
	Sphere* selected = nullptr;

	glm::vec3 intersectionWorldPos, surfaceNormal;

	for (auto sphere : spheres)
	{
		float intersectionDistance = farPlane;
		if (sphere->ray_intersect(rayOrigin, rayDirection, intersectionDistance) && intersectionDistance < zDistance)
		{
			selected = sphere;
			zDistance = intersectionDistance;
			intersectionWorldPos = rayOrigin + rayDirection * intersectionDistance;
			surfaceNormal = glm::normalize(intersectionWorldPos - sphere->_center);
		}
	}
	auto total_diffuse_contribution = 0.f;
	auto total_specular_contribution = 0.f;
	for (auto light : lights)
	{
		glm::vec3 lightDirection = glm::normalize(light->position - intersectionWorldPos); //get light direction vec
		float lightDistance = glm::distance(light->position, intersectionWorldPos);

		glm::vec3 shadowRayOrigin = intersectionWorldPos + surfaceNormal * 1e-3f * (glm::dot(lightDirection, surfaceNormal) < 0.f ? - 1.f: 1.f);

		bool inShadow = false;
		for (auto sphere : spheres)
		{
			float intersectionDistance = farPlane;
			if (sphere->ray_intersect(shadowRayOrigin, lightDirection, intersectionDistance))
			{
				glm::vec3 shadowHitPointWorldPos = shadowRayOrigin + lightDirection * intersectionDistance;
				if (glm::distance(shadowHitPointWorldPos, shadowRayOrigin) < lightDistance) {
					inShadow = true;
					break;
				}
			}
		}
		
		if (inShadow) continue;
		// Lambert lighting with clamping it with zero.
		total_diffuse_contribution += light->intensity * std::max(0.f, glm::dot(surfaceNormal, lightDirection));
		if (selected != nullptr)
		{
			const auto specular = std::max(0.f, glm::dot(glm::reflect(lightDirection, surfaceNormal),-rayDirection));
			total_specular_contribution += light->intensity * glm::pow(specular, selected->material->specular_power) * selected->material->reflectivity;
		}
	}

	if (selected != nullptr)
	{
		auto val = selected->material->diffuse * total_diffuse_contribution + selected->material->specular_color * total_specular_contribution;
		return val;
	}
	else
		return glm::vec3(0.2, 0.7, 0.8);
}

