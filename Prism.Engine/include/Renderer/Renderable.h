#pragma once
#include <glm/glm.hpp>
#include <tuple>
#include <map>
#include "Renderer/Animation.h"
#include "Math/Vector3f.h"
#include "Renderer/Graphics/Models/Model.h"
#include <functional>

class Renderable
{
public:
	Renderable();
	/// <summary>
	///  returns a mat4 based on the position, rotation and scale
	/// </summary>
	glm::mat4 getMatrix() const;
	~Renderable();

	Renderer::Graphics::Models::Model* model;
	std::tuple<float, float, float> position;
	std::tuple<float, float, float> rotation;
	std::tuple<float, float, float> scale;
	Math::Vector3f color;

	std::map<Renderer::Animation, std::tuple<float, bool>> currentAnimations;
};

