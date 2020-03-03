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

void Raytracer::fill_frame_buffer()
{
	for (size_t j = 0; j < height; j++)
	{
		for (size_t i = 0; i < width; i++)
		{
			float diffX = (2 * (i * .5f) / (float)width - 1);
			float _fov = glm::tan(fov / 2.f);
			float x = diffX * _fov * width / (float)height;
			float diffY = -(2 * (j * .5f) / (float)height - 1);
			float y = diffY * glm::tan(fov / 2.f);
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
			const auto target_pixel = frame_buffer_[i + j * width];
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
	float zDistance = 1000.f;
	Sphere* selected = nullptr;
	for (auto sphere : spheres)
	{
		float sphereDistance = 1000.f;
		if (sphere->ray_intersect(rayOrigin, rayDirection, sphereDistance) && sphereDistance < zDistance)
		{
			selected = sphere;
			zDistance = sphereDistance;
		}
	}
	if (selected != nullptr)
		return selected->material->diffuse;
	else
		return glm::vec3(0.4, 0.4, 0.3);
}
