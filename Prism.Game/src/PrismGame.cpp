#include "PrismGame.h"



/// <summar>
/// creates new PrismGame object
/// </summary>
PrismGame::PrismGame() {
	entityManager = std::make_shared<EntityManager>();
	systemManager = std::make_shared<SystemManager>();
	createPlayer();
	registerSystems();
}

/// <summary>
/// create player entity
/// </summary>
void PrismGame::createPlayer() {
	// TODO: Deze functie moet later verplaatst worden naar een Factory of iets dergelijks.

	Renderer::Graphics::Loader::ModelLoader ml = Renderer::Graphics::Loader::ModelLoader();
	Model* model = ml.loadModel("./res/bunny.obj");

	VelocityComponent velocity;
	PositionComponent position;
	DragComponent drag;
	drag.force = 0.001f;
	KeyboardInputComponent input;
	AppearanceComponent appearance;
	appearance.translationZ = 1;
	appearance.scaleX = 1;
	appearance.scaleY = 1;
	appearance.scaleZ = 1;
	appearance.model = model;

	entityManager->createEntity(velocity, position, drag, input, appearance);
}

/// <summar>
/// register systems in system manager
/// </summary>
void PrismGame::registerSystems()
{
	MotionSystem motionSystem = MotionSystem(entityManager);
	// TODO: Maak een initialisatiefunctie waarbij deze waardes uit de context gehaald kunnen worden.
	RenderSystem renderSystem = RenderSystem(entityManager, 1920, 1080);
	KeyboardInputSystem inputSystem = KeyboardInputSystem(entityManager);
	systemManager->registerSystem(motionSystem);
	systemManager->registerSystem(renderSystem);
	systemManager->registerSystem(inputSystem);
}

void PrismGame::onUpdate(Context &context)
{
	auto inputSystem = systemManager->getSystem<KeyboardInputSystem>();
	auto motionSystem = systemManager->getSystem<MotionSystem>();
	auto renderSystem = systemManager->getSystem<RenderSystem>();

	inputSystem->update(context);
	motionSystem->update(context);
	renderSystem->update(context);

	for (auto &entity : entityManager->getAllEntitiesWithComponent<VelocityComponent>()) {
		auto velocity = entity.component;
		auto position = entityManager->getComponent<PositionComponent>(entity.id);
		printf("Entity:\t\t%d \nPosition: \tX: %.2f, Y: %.2f\nVelocity:\tdX: %.2f, dY: %.2f\n\n", entity.id, position->x, position->y, velocity->dx, velocity->dy);
	}
}
void PrismGame::onEnter() {
}
void PrismGame::onLeave() {
}

PrismGame::~PrismGame()
= default;
