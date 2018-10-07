#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <tuple>

using namespace std;
using namespace glm;

namespace Renderer {
	class Camera
	{
	public:
		Camera();
		mat4 getCameraMatrix();
		void move(float x, float y, float z);
		void rotate(float x, float y, float z);
		~Camera();
	private:
		vec3 position;
		vec3 rotation;
		vec3 cameraDirection;
		vec3 cameraUp;
		vec3 worldUp;
	};
}