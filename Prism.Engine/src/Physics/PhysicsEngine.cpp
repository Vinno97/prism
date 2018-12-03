#include "Physics/PhysicsEngine.h"

#include <Box2D/Box2D.h>

PhysicsEngine::PhysicsEngine()
{
	b2Vec2 gravity(0.0f, 0.0f);	b2World world(gravity);
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);
}

