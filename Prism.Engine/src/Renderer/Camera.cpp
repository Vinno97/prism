#include "Renderer/Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

using namespace glm;

namespace Renderer {
	Camera::Camera()
	{
		position = vec3(-45.f, 4.f, 10.f);
		target = vec3(-45.f, 0.f, -15.f);
	}

	mat4 Camera::getCameraMatrix() const
	{
		return glm::lookAt(position, target, glm::vec3(0.f, 1.f, 0.f));
	}

	void Camera::move(float x, float y, float z)
	{
		position.x += x;
		position.y += y;
		position.z += z;
	}

	void Camera::moveTarget(float x, float y, float z)
	{
		target.x += x;
		target.y += y;
		target.z += z;
	}

	Camera::~Camera()
	{
	}
}