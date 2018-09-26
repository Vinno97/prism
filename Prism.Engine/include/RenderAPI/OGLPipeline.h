#pragma once
#include "RenderAPI/Pipeline.h"
#include "RenderAPI/VertexShader.h"
#include "RenderAPI/FragmentShader.h"
#include <map>
#include <glm/glm.hpp>

namespace RenderAPI {
	class OGLPipeline : public Pipeline
	{
	public:
		OGLPipeline(VertexShader* vs, FragmentShader* fs);
		~OGLPipeline();
		void run() override;	
		void stop() override;
		bool createUniform(const char* name) override;
		bool setUniformMatrix4f(const char* name, glm::mat4 matrix) override;
		bool setUniformVector(const char* name, float x, float y, float z) override;

		std::map<std::string, int> uniforms;
	};
}
