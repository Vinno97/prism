#include "Renderer/Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

using namespace glm;

namespace Renderer {
	Camera::Camera()
	{
		position = vec3(0.f, 0.f, 0.f);
		rotation = vec3(0.f, 0.f, -1.f);
		cameraUp = vec3(0.0f, 1.0f,  0.0f);
		cameraDirection = vec3(0.0f, 0.0f, -1.f);
		worldUp = cameraUp;
	}

	mat4 Camera::getCameraMatrix()
	{
//		mat4 cameraMatrix = lookAt(
//			position,         
//			position+cameraDirection, 
//			cameraUp 
//		);

		        // First do the rotation so camera rotates over its position
   //     viewMatrix.rotate((float)Math.toRadians(rotation.x), new Vector3f(1, 0, 0))
    //        .rotate((float)Math.toRadians(rotation.y), new Vector3f(0, 1, 0));

		mat4 cameraMatrix = mat4(1.f);
		cameraMatrix = translate(cameraMatrix, position);
		cameraMatrix = glm::rotate(cameraMatrix, radians(rotation.x), vec3(1.f, 0.f, 0.f));
		cameraMatrix = glm::rotate(cameraMatrix, radians(rotation.y), vec3(0.f, 1.f, 0.f));
		cameraMatrix = inverse(cameraMatrix);
		return cameraMatrix;
	}

	void Camera::move(float x, float y, float z)
	{
		position.x += x;
		position.y += y;
		position.z += z;
	}

	void Camera::rotate(float x, float y, float z)
	{
		rotation.x += x;
		rotation.y += y;
		rotation.z += z;
	}

	Camera::~Camera()
	{
	}
}