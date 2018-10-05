#include "Renderer/ForwardRenderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Graphics/VertexShader.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLVertexShader.h"
#include "Renderer/Graphics/OpenGL/OGLPipeline.h"
#include "Renderer/Graphics/VertexArrayObject.h"
#include "Renderer/Graphics/VertexBuffer.h"
#include "Renderer/Graphics/Loader/ModelLoader.h"
#include "Renderer/Graphics/Models/Model.h"

using namespace Renderer::Graphics;

namespace Renderer {

	ForwardRenderer::ForwardRenderer()
	{

		renderDevice = 

		const char* vertexShaderSource = { \
			"#version 330 core\n\
			layout (location = 0) in vec3 aPos; \
			layout (location = 1) in vec3 colour; \
			out vec4 pass_colour;\
			uniform mat4 model;\
			uniform mat4 view;\
			uniform mat4 proj; \
			void main() { \
				gl_Position = proj * view * model * vec4(aPos.x, aPos.y, aPos.z, 1 ); \
				pass_colour = view * model * vec4(aPos.x, aPos.y, aPos.z, 1); \
			}"
		};
	
		const char* fragmentShaderSource =
		{
			"#version 330 core\n\
			in vec4 pass_colour; \
			out vec4 FragColor; \
			void main() { \
				FragColor = pass_colour*-1; \
			}"
		};

		VertexShader* vertexShader = renderDevice->createVertexShader(vertexShaderSource);
		FragmentShader* fragmentShader = renderDevice->createFragmentShader(fragmentShaderSource);
		geometryPipeline = renderDevice->createPipeline(vertexShader, fragmentShader);


	}


	ForwardRenderer::~ForwardRenderer()
	{
		delete geometryPipeline;
	}
}
