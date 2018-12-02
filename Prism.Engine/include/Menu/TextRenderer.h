#include <GL/glew.h>
#include <string>
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Graphics/VertexShader.h"
#include "Renderer/Graphics/Texture.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"
#include "Renderer/Graphics/VertexArrayObject.h"
#include "Renderer/Graphics/VertexBuffer.h"
#include "Menu/TextControl.h"
#include "Util/FileSystem.h"
#include <functional>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include <string>
#include <memory>

#pragma once
struct Character {
	std::shared_ptr<Renderer::Graphics::Texture> texture;  // ID handle of the glyph texture
	glm::ivec2 Size;       // Size of glyph
	glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
	unsigned int Advance;    // Offset to advance to next glyph
};

class TextRenderer
{
public:
	TextRenderer();
	~TextRenderer()=default;
	void RenderText(const Menu::TextControl& control);

	std::unique_ptr<Renderer::Graphics::Pipeline> textPipeline;
	Renderer::Graphics::RenderDevice* renderDevice;

private:
	std::map<char, Character> Characters;

	std::unique_ptr<Renderer::Graphics::VertexBuffer> VBO2;
	std::unique_ptr<Renderer::Graphics::VertexArrayObject> VAO2;
};

