#pragma once

#include "Context.h"
#include "ECS/Systems/System.h"
#include "Physics/QuadTree.h"
#include "Physics/AABBCollider.h"

class CollisionSystem : public ECS::Systems::System{
public:
	CollisionSystem(std::shared_ptr<ECS::EntityManager> entityManager, float width, float height, float posX, float posY);
	~CollisionSystem();
	void update(Context context) override;
private:
	QuadTree quadTree;
	AABBCollider aabbCollider;
};


	
