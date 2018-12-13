#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <tuple>

namespace Renderer {
	class Camera
	{
	public:
		Camera();
		/// <summary>
		/// Returns a 4f matrix with the camera transformation
		/// </summary>
		glm::mat4 getCameraMatrix() const;
		
		/// <summary>
		/// Translates the camera by the values given
		/// </summary>
		void move(const float x, const float y, const float z);

		/// <summary>
		/// Translates the camera by the values given
		/// </summary>
		void moveTarget(const float x, const float y, const float z);

		// TODO: Deze moeten mss enkel readonly getters zijn (en dat het renderSystem gewoon de delta voor move() uitrekent).
		glm::vec3 position;
		glm::vec3 target;
		~Camera();
	};
}