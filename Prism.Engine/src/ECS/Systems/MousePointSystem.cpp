#include "ECS/Systems/MousePointSystem.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Context.h"
#include "ECS/Components/CameraComponent.h"

namespace ECS {
	namespace Systems {
		MousePointSystem::MousePointSystem(EntityManager& entityManager) : System(entityManager) {
			
		}

		MousePointSystem::~MousePointSystem()
			= default;

		void MousePointSystem::update(Context& context) {
			auto input = context.inputManager;

			auto cameraEntity = this->entityManager->getAllEntitiesWithComponent<CameraComponent>()[0].component;

			cameraEntity->camera;

			if (input->isMouseButtonPressed(Key::MOUSE_BUTTON_LEFT))
			{
				std::vector<int> pos = input->GetMousePoisiton();
				float x = (2.0f * pos[0]) / context.window->width - 1.0f;
				float y = 1.0f - (2.0f * pos[1]) / context.window->height;
				float z = 1.0f;
				  
				glm::vec3 ray_nds{x, y, z};
				glm::vec4 clip_coords{ ray_nds.x, ray_nds.y, - 1.0f, 1.0f };
				auto projection = glm::perspective(glm::radians(45.0f), (float)context.window->width / (float)context.window->height, 1.f, 100.0f);
				auto invertedProjection = glm::inverse(projection);
				glm::vec4 eye_coords = invertedProjection * clip_coords;
				eye_coords = glm::vec4(eye_coords.x, eye_coords.y, -1.0, 0.0);

				glm::vec3 normal{ 0, 1, 0 };//Direction of plane

				glm::mat4 matrix = cameraEntity->camera.getCameraMatrix();
				auto invertedCamera = glm::inverse(matrix);
				glm::vec3 ray_wor = invertedCamera * eye_coords; 
				ray_wor = glm::normalize(ray_wor);

		    	float denom = glm::dot(normal, ray_wor);
				glm::vec3 ray_org = cameraEntity->camera.position;

		

		    	if (abs(denom) > 0.0001f) // your favorite epsilon
		    	{						// this is the position of the plane
					auto entities = entityManager->getAllEntitiesWithComponent<MousePointerComponent>();
					if (entities.size() <= 0)
						return;

					auto mouseEntityID = entities[0];
					float t = glm::dot((vec3(0, 0, 0) - ray_org), normal) / denom;
					if (t >= 0) {
						auto mousePosition3D = entityManager->getComponent<PositionComponent>(mouseEntityID.id);
						glm::vec3 intersection = ray_org + (ray_wor * t);

						mousePosition3D->y = intersection.z;
						mousePosition3D->x = intersection.x;
					}
		    	}
			}
		}

		System * MousePointSystem::clone()
		{
			return new MousePointSystem(*entityManager);
		}
	}
}
