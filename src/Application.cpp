#include "Raytracer.h"
int main()
{
	Sphere* sphere = new Sphere(glm::vec3(.7f, -.4f, 4), .2f);
	Sphere* sphere2 = new Sphere(glm::vec3(.3f, -.2f, 4), .2f);
	std::vector<Sphere*> spheres = { sphere,sphere2 };
	Raytracer* tracer = new Raytracer(1920, 1080);
	tracer->set_render_targets(spheres);
	tracer->render();
}

