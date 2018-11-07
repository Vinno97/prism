#include "Renderer/Renderable.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <tuple>

Renderable::Renderable()
{
	position = tuple<float, float, float>(0.f, 0.f, 0.f);
	rotation = tuple<float, float, float>(0.f, 0.f, 0.f);
	//Init scale with 1.f to prevent objects from disappearing immediately
	scale = tuple<float, float, float>(1.f, 1.f, 1.f);
}

glm::mat4 Renderable::getMatrix() const
{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(get<0>(position), get<1>(position), get<2>(position)));
		model = glm::scale(model, glm::vec3(get<0>(scale), get<1>(scale), get<2>(scale)));
		model = glm::rotate(model, glm::radians(get<0>(rotation)), glm::vec3(1.f, 0.f, 0.f)); //Rotate x
		model = glm::rotate(model, glm::radians(get<1>(rotation)), glm::vec3(0.f, 1.f, 0.f)); //Rotate y
		model = glm::rotate(model, glm::radians(get<2>(rotation)), glm::vec3(0.f, 0.f, 1.f)); //Rotate z
		return model;
}

Renderable::~Renderable()
{
}
