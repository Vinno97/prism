#include "Renderer/Renderable.h"

#include <tuple>

Renderable::Renderable()
{
	position = tuple<float, float, float>(0.f, 0.f, 0.f);
	rotation = tuple<float, float, float>(0.f, 0.f, 0.f);
	scale = tuple<float, float, float>(0.f, 0.f, 0.f);
}

Renderable::~Renderable()
{
}
