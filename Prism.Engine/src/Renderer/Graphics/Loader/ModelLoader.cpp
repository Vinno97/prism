#pragma once
#include <glm/glm.hpp>
#include "Renderer/Graphics/RenderDevice.h"
#include "Renderer/Graphics/OpenGL/OGLRenderDevice.h"
#include "Renderer/Graphics/IndexBuffer.h"
#include "Renderer/Graphics/VertexBuffer.h"
#include "Renderer/Graphics/Loader/ModelLoader.h"
#include "Renderer/Graphics/Loader/StaticMeshLoader.h"
#include "Renderer/Graphics/Models/Model.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace Renderer::Graphics;
using namespace Renderer::Graphics::OpenGL;
using namespace Renderer::Graphics::Models;

namespace Renderer {
	namespace Graphics {
		namespace Loader {
			ModelLoader::ModelLoader(RenderDevice* renderDevice)
			{
				this->renderDevice = renderDevice;
			}
			
			Model* ModelLoader::loadModel(string path)
			{
				StaticMeshLoader staticMeshLoader = StaticMeshLoader();
				Mesh* m = staticMeshLoader.loadMesh(path, this->renderDevice);
				return new Model(m);
			}
		}
	}
}