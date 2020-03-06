#pragma once
#include <iostream>
#include <vector>
#include <glm.hpp>
#include "Sphere.h"
#include "Light.h"
#include <algorithm>

class Raytracer
{
public:
	Raytracer(int width, int height)
		:frame_buffer_(width* height), width(width), height(height), fov(75){}
	void set_render_targets(std::vector<Sphere*>& spheres);
	void set_lights(std::vector<Light*>& lights);
	void render();

private:
	void fill_frame_buffer();
	void push_to_pixel_buffer();
	void write_image_to_disk();
	///Return pixel color info
	glm::vec3 cast_ray(const glm::vec3& rayOrigin, const glm::vec3 rayDirection,int depth, Sphere* _selected = nullptr);

private:
	std::vector<glm::vec3> frame_buffer_;
	uint8_t* pixels;
	int width;
	int height;
	const float fov;
	const float farPlane = 1000.f;

private:
	std::vector<Sphere*> spheres;
	std::vector<Light*> lights;

private:
	glm::vec3 clamp_color(const glm::vec3 color)
	{
		const auto max = std::max(color.r, std::max(color.g, color.b));
		return color / max;
	}

};
