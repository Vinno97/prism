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
		/// <summary>
		/// Returns a 4f matrix with the camera transformation
		/// </summary>
		mat4 getCameraMatrix();
		
		/// <summary>
		/// Translates the camera by the values given
		/// </summary>
		void move(float x, float y, float z);

		/// <summary>
		/// Translates the camera by the values given
		/// </summary>
		void rotate(float x, float y, float z);
		~Camera();
	private:
		vec3 position;
		vec3 rotation;
	};
}