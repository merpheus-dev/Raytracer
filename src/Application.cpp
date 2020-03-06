#include "Raytracer.h"
int main()
{
	Material* red = new Material(glm::vec3(1., 0., 0.),glm::vec3(1.f),50.f,.9f);
	Material* green = new Material(glm::vec3(.55, .47, .87), glm::vec3(1.f), 10.f,.1f);
	Sphere* sphere = new Sphere(glm::vec3(.45f, -.4f,3.4f), .1f, red);
	Sphere* sphere2 = new Sphere(glm::vec3(.8f, -.3f, 4), .2f,green);
	Sphere* sphere3 = new Sphere(glm::vec3(.83f, -.2f, 3.f), .1f,red);
	Light* light = new Light(glm::vec3(.1f, -.7f, 2.), 1.2);
	Light* light2 = new Light(glm::vec3(1.f, .3f, 2.),.8);
	std::vector<Light*> lights = { light,light2 };
	std::vector<Sphere*> spheres = { sphere2,sphere };
	Raytracer* tracer = new Raytracer(1920, 1080);
	tracer->set_lights(lights);
	tracer->set_render_targets(spheres);
	tracer->render();
}

