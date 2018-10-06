#pragma once

#include <tuple>
#include "Renderer/Graphics/Models/Model.h"

using namespace Renderer::Graphics::Models;

class Renderable
{
public:
	Renderable();
	~Renderable();

	Model* model;
	tuple<float, float, float> position;
	tuple<float, float, float> rotation;
	tuple<float, float, float> scale;
};

