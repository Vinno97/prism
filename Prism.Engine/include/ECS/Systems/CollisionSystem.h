#pragma once

#include "Context.h"
#include "ECS/Systems/System.h"
#include "Physics/QuadTree.h"

class CollisionSystem : public ECS::Systems::System{
public:
	CollisionSystem(float width, float height, float posX, float posY, std::shared_ptr<ECS::EntityManager> entityManager);
	~CollisionSystem();
	void update(Context context) override;
private:
	QuadTree quadTree;
};


	
