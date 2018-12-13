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
#include <memory>

using namespace std;
using namespace Renderer::Graphics;
using namespace OpenGL;
using namespace Models;

namespace Renderer
{
	namespace Graphics
	{
		namespace Loader
		{
			unique_ptr<Model> ModelLoader::loadModel(string path)
			{
				StaticMeshLoader staticMeshLoader = StaticMeshLoader();
				shared_ptr<Mesh> m = staticMeshLoader.loadMesh(path);
				unique_ptr<Model> model = make_unique<Model>(m);
				return model;
			}
		}
	}
}
