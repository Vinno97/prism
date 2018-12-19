#pragma once

namespace Renderer {
	namespace Graphics {
		class Pipeline
		{
		public:
			Pipeline()=default;

			/// <summary>
			/// Start this pipeline
			/// </summary> 
			virtual void run() = 0;

			/// <summary>
			/// Stop this pipeline
			/// </summary> 
			virtual void stop() = 0;

			/// <summary>
			/// Find and register the uniform with this name
			/// </summary> 
			virtual bool createUniform(const char* name) = 0;

			/// <summary>
			/// Set the uniform to a specific matrix
			/// </summary> 
			virtual bool setUniformMatrix4f(const char* name, glm::mat4 matrix) = 0;

			/// <summary>
			/// Set the uniform to a specific vector
			/// </summary> 
			virtual bool setUniformVector(const char* name, float x, float y, float z) = 0;

			/// <summary>
			/// Set the uniform to a specific integer
			/// </summary> 
			virtual bool setUniformInt(const char* name, int value) = 0;

			/// <summary>
			/// Set the uniform to a specific float 
			/// </summary> 
			virtual bool setUniformFloat(const char* name, float value) = 0;
			GLuint pipelineID;
		};
	}
}