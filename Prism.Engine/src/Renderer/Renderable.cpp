#include "Renderer/Renderable.h"

#include <tuple>

Renderable::Renderable()
{
	position = tuple<float, float, float>(0.f, 0.f, 0.f);
	rotation = tuple<float, float, float>(0.f, 0.f, 0.f);
	//Init scale with 1.f to prevent objects from disappearing immediately
	scale = tuple<float, float, float>(1.f, 1.f, 1.f);
}

Renderable::~Renderable()
{
}
