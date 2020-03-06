#include "Raytracer.h"
int main()
{
	Material* red = new Material(glm::vec3(1., 0., 0.),glm::vec3(1.f),50.f,.9f,0.);
	Material* green = new Material(glm::vec3(.55, .47, .87), glm::vec3(1.f), 10.f, .1f,0.);
	Material* mirror = new Material(glm::vec3(1., 1., 1.), glm::vec3(0.f), 10.f,.1f,1.f);
	Sphere* sphere = new Sphere(glm::vec3(.4f, -.25f,3.4f), .1f, red);
	Sphere* sphere2 = new Sphere(glm::vec3(.8f, -.3f, 4), .2f,green);
	Sphere* sphere3 = new Sphere(glm::vec3(1.2f, -.5f, 4.f), .1f,red);
	Sphere* sphere4 = new Sphere(glm::vec3(.8f, -.1f, 3.f), .1f, green);
	Light* light = new Light(glm::vec3(.1f, -.3f, 2.), 1.2);
	Light* light2 = new Light(glm::vec3(1.f, -.3f, 2.), .8);
	Light* light3 = new Light(glm::vec3(-.1f, -.3f, 2.), .8);
	std::vector<Light*> lights = { light,light2,light3};
	std::vector<Sphere*> spheres = { sphere2,sphere ,sphere3,sphere4};
	Raytracer* tracer = new Raytracer(1920, 1080);
	tracer->set_lights(lights);
	tracer->set_render_targets(spheres);
	tracer->render();
}

