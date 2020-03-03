#include "Raytracer.h"
#include "stb_image_write.h"
int main()
{
	Sphere* sphere = new Sphere(glm::vec3(.7f, -.4f, 4), .2f);
	Raytracer* tracer = new Raytracer(1920, 1080);
	tracer->render(sphere);
}

