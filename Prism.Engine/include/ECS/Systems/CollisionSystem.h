#pragma once

#include "Context.h"
#include "ECS/Systems/System.h"
#include "Physics/QuadTree.h"
#include "Physics/AABBCollider.h"

class CollisionSystem : public ECS::Systems::System{
public:
	CollisionSystem(ECS::EntityManager &entityManager, float width, float height, float posX, float posY);
	~CollisionSystem();
	void update(Context context) override;
	ECS::Systems::System* clone() override;
private:
	QuadTree quadTree;
	AABBCollider aabbCollider;
};


	
