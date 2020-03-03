#include "Raytracer.h"
int main()
{
	Material* red = new Material(glm::vec3(1., 0., 0.));
	Material* green = new Material(glm::vec3(0., 1., 0.));
	Sphere* sphere = new Sphere(glm::vec3(.7f, -.4f, 5), .2f,red);
	Sphere* sphere2 = new Sphere(glm::vec3(.8f, -.3f, 4), .2f,green);
	std::vector<Sphere*> spheres = { sphere,sphere2 };
	Raytracer* tracer = new Raytracer(1920, 1080);
	tracer->set_render_targets(spheres);
	tracer->render();
}

