#pragma once
#include <glm/glm.hpp>
#include <tuple>
#include "Math/Vector3f.h"
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

	Model* model;
	tuple<float, float, float> position;
	tuple<float, float, float> rotation;
	tuple<float, float, float> scale;
	Math::Vector3f color;
};

