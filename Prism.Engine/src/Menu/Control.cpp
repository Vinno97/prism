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
	Control::Control(float x, float y, float width, float height)
	{
		GLuint TextureID = 0;

		glGenTextures(1, &TextureID);
		glBindTexture(GL_TEXTURE_2D, TextureID);

		Surface = IMG_Load("C:\\prism\\someimage.png");
		if (Surface == nullptr)
		{
			std::string errorMessage = "error";
			throw std::runtime_error(errorMessage);
		}

		int Mode = GL_RGB;

		if (Surface->format->BytesPerPixel == 4) {
			Mode = GL_RGBA;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, Mode, Surface->w, Surface->h, 0, Mode, GL_UNSIGNED_BYTE, Surface->pixels);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


		position = Math::Vector3f{ x, y, 0 };
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

	void Control::UpdateTexture(const char *path)
	{
		Surface = IMG_Load(path);
	}
	//menuBuilder.addControl(20, 865, 300, 75);

	void Control::DrawTexture()
	{
		// For Ortho mode, of course
		int X = 20;
		int Y = 865;
		int Width = 300;
		int Height = 75;

		glBegin(GL_QUADS);
			glTexCoord2f(0, 0); glVertex3f(X, Y, 0);
			glTexCoord2f(1, 0); glVertex3f(X + Width, Y, 0);
			glTexCoord2f(1, 1); glVertex3f(X + Width, Y + Height, 0);
			glTexCoord2f(0, 1); glVertex3f(X, Y + Height, 0);
		glEnd();
	}
}