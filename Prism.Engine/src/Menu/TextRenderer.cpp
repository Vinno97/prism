
#include <ft2build.h>
#include FT_FREETYPE_H  

#include "Menu/TextRenderer.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"

using namespace Renderer::Graphics;
using namespace Renderer::Graphics::OpenGL;

TextRenderer::TextRenderer()
{
	renderDevice = OGLRenderDevice::getRenderDevice();

	FT_Library ft;
	if (FT_Init_FreeType(&ft))
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

	FT_Face face;
	if (FT_New_Face(ft, "./res/fonts/square.ttf", 0, &face))
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

	FT_Set_Pixel_Sizes(face, 0, 48);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

	for (auto c = 0; c < 128; c++)
	{
		// Load character glyph 
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// Generate texture
		auto texture = renderDevice->createTexture(face->glyph->bitmap.width, face->glyph->bitmap.rows, face->glyph->bitmap.buffer, false);

		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		Characters.insert(std::pair<GLchar, Character>(c, character));

	}

	VAO2 = renderDevice->createVertexArrayobject();
	VAO2->bind();

	VBO2 = renderDevice->createDynamicVertexBuffer();
	VAO2->addVertexBuffer(VBO2.get(), 0, 4 * sizeof(GLfloat), 0, 4);
	VAO2->unbind();

	Util::FileSystem fileReader;
	std::string vertexSource = fileReader.readResourceFileIntoString("/shaders/textShader.vs");
	std::string fragmentSource = fileReader.readResourceFileIntoString("/shaders/textShader.fs");
	std::unique_ptr<VertexShader> vertexShader = renderDevice->createVertexShader(vertexSource.c_str());
	std::unique_ptr<FragmentShader> fragmentShader = renderDevice->createFragmentShader(fragmentSource.c_str());
	textPipeline = std::move(renderDevice->createPipeline(*vertexShader, *fragmentShader));

	textPipeline->createUniform("textColor");
}

void TextRenderer::RenderText(const Menu::TextControl& control)
{
	// Activate corresponding render state	
	textPipeline->run();
	textPipeline->setUniformVector("textColor", control.colour.x, control.colour.y, control.colour.z);
	renderDevice->useBlending(true);
	VAO2->bind();

	float x = control.position.x;
	float y = control.position.y;

	// Iterate through all characters
	std::string::const_iterator c;
	for (c = control.text.begin(); c != control.text.end(); c++)
	{
		Character ch = Characters[*c];

		GLfloat xpos = x + ch.Bearing.x * control.scale;
		GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * control.scale;

		GLfloat w = ch.Size.x * control.scale;
		GLfloat h = ch.Size.y * control.scale;
		// Update VBO for each character
		GLfloat vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};
		// Render glyph texture over quad
	//	glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		ch.texture->bind(textures[0]);
		// Update content of VBO memory
		VBO2->bind();
		VBO2->rebuffer(sizeof(vertices), vertices);
		VBO2->unbind();
		// Render quad
		renderDevice->DrawTriangles(0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * control.scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
	}

	VAO2->unbind();

	renderDevice->useBlending(false);
}
