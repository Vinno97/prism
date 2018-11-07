#pragma once
#include <glm/glm.hpp>
#include <tuple>
#include "Renderer/Graphics/Models/Model.h"

using namespace Renderer::Graphics::Models;

class Renderable
{
public:
	Renderable();
	/// <summary>
	///  returns a mat4 based on the position, rotation and scale
	/// </summary>
	glm::mat4 getMatrix() const;
	~Renderable();

	std::shared_ptr<Model> model;
	tuple<float, float, float> position;
	tuple<float, float, float> rotation;
	tuple<float, float, float> scale;
};

