#pragma once
#include "Renderer/Graphics/Pipeline.h"
#include "Renderer/Graphics/VertexShader.h"
#include "Renderer/Graphics/FragmentShader.h"
#include <map>
#include <glm/glm.hpp>
#include <memory>

namespace Renderer {
	namespace Graphics {
		namespace OpenGL {
			class OGLPipeline : public Pipeline
			{
			public:
				OGLPipeline(VertexShader& vs, FragmentShader& fs);
				~OGLPipeline();
				void run() override;
				void stop() override;
				bool createUniform(const char* name) override;
				bool setUniformMatrix4f(const char* name, glm::mat4 matrix) override;
				bool setUniformVector(const char* name, float x, float y, float z) override;
				bool setUniformFloat(const char* name, float value) override;
				std::map<std::string, int> uniforms;
			};
		}
	}
}