#include "Menu/Control.h"
#include <vector>
#include <memory>
#include "Renderer/Graphics/Models/Model.h"
#include "Renderer/Graphics/Models/Mesh.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"
#include "Renderer/Graphics/Models/Mesh.h"
#include "Renderer/Graphics/RenderDevice.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

using namespace std;
using namespace Renderer::Graphics;
using namespace Renderer::Graphics::OpenGL;
using namespace Renderer::Graphics::Models;

namespace Menu {
	Control::Control(float x, float y, float width, float height, const char *path)
	{
		// Image is SDL_surface
		this->surface = IMG_Load(path);

		if (!surface)
		{
			std::cout << "Error Cannot load image";
		}

		this->xPos = x;
		this->yPos = y;

		position = Math::Vector3f{ this->xPos, this->yPos, 0 };
		size = Math::Vector3f{width, height, 0};

		RenderDevice* renderDevice = OGLRenderDevice::getRenderDevice();

		float vertices[] = {
			 1.0f,  1.0f,  // top right
			 1.0f,  0.0f,  // bottom right
			 0.0f,  0.0f,  // bottom left
			 0.0f,  1.0f   // top left 
		};
		unsigned int indices[] = {  // note that we start from 0!
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};

		float* verticesArray = vertices;
		unsigned int* indicesArray = indices;

		auto verticesSize = 8 * sizeof(float);

		unique_ptr<VertexBuffer> vertexBuffer = renderDevice->createVertexBuffer(verticesSize, verticesArray);

		std::unique_ptr<VertexArrayObject> vertexArrayObject = renderDevice->createVertexArrayobject();
		vertexArrayObject->addVertexBuffer(move(vertexBuffer), 0, 2 * sizeof(float), 0, 2);

		unique_ptr<IndexBuffer> indexBuffer = renderDevice->createIndexBuffer(6 * sizeof(unsigned int), indicesArray);

		shared_ptr<Mesh> mesh = make_shared<Mesh>(move(vertexArrayObject), move(indexBuffer));

		mesh->isIndiced = true;
		mesh->indicesLength = 6;
		model = Model{ mesh };
	}

	void Control::DrawTexture()
	{
		glPushMatrix(); //Start phase

		glOrtho(0, 720, 480, 0, -1, 1); //Set the matrix


		GLuint mTextureWidth = this->surface->w;
		GLuint mTextureHeight = this->surface->h;

		glEnable(GL_TEXTURE_2D);

		//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		GLuint textures;
		glGenTextures(1, &textures); //Number of textures stored in array name specified

		glBindTexture(GL_TEXTURE_2D, textures);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		// Map the surface to the texture in video memory
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->surface->w, this->surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels); //GL_BITMAP
		//SDL_FreeSurface(image);


		glBindTexture(GL_TEXTURE_2D, textures);

		//Render texture quad
		glBegin(GL_QUADS);
			glTexCoord2f(0.f, 0.f); glVertex2f(this->xPos, this->yPos); //Bottom left
			glTexCoord2f(1.f, 0.f); glVertex2f(this->xPos + this->surface->w, this->yPos); //Bottom right
			glTexCoord2f(1.f, 1.f); glVertex2f(this->xPos + this->surface->w, this->yPos + this->surface->h); //Top right
			glTexCoord2f(0.f, 1.f); glVertex2f(this->xPos, this->yPos + this->surface->h); //Top left
		glEnd();

		glDisable(GL_TEXTURE_2D);


		glPopMatrix(); //End rendering phase
	}

	void Control::UpdateTexture(const char *path)
	{
		this->surface = IMG_Load(path);

		if (!surface)
		{
			std::cout << "Error Cannot load image";
		}

	}
}