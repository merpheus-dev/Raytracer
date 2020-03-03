#pragma once
#include <iostream>
#include <vector>
#include <glm.hpp>
#include "Sphere.h"
class Raytracer
{
public:
	Raytracer(int width, int height)
		:frame_buffer_(width* height), width(width), height(height), fov(75), sphere(nullptr){}
	void render(Sphere* _sphere);

private:
	void fill_frame_buffer();
	void push_to_pixel_buffer();
	void write_image_to_disk();
	glm::vec3 cast_ray(const glm::vec3& rayOrigin, const glm::vec3 rayDirection);

private:
	std::vector<glm::vec3> frame_buffer_;
	uint8_t* pixels;
	int width;
	int height;
	const float fov;

	Sphere* sphere;
};
