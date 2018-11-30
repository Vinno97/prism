#include <GL/glew.h>
#include <string>
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Graphics/VertexShader.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLVertexShader.h"
#include "Renderer/Graphics/OpenGL/OGLPipeline.h"
#include "Renderer/Graphics/VertexArrayObject.h"
#include "Renderer/Graphics/VertexBuffer.h"
#include "Util/FileSystem.h"
#include <functional>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include <string>
#include <memory>
#include <SDL2/SDL_opengl.h>

#pragma once
struct Character {
	unsigned int TextureID;  // ID handle of the glyph texture
	glm::ivec2 Size;       // Size of glyph
	glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
	unsigned int Advance;    // Offset to advance to next glyph
};

class TextRenderer
{
public:
	TextRenderer();
	~TextRenderer();
	void RenderText(std::string text, float x, float y, float scale);

	std::unique_ptr<Renderer::Graphics::Pipeline> textPipeline;
	Renderer::Graphics::RenderDevice* renderDevice;

private:
	std::map<GLchar, Character> Characters;
	GLuint VAO, VBO;
};

