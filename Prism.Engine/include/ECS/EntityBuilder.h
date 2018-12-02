#pragma once
#include "ECS/Components/ResourceGatherComponent.h"
#include "EntityManager.h"

class EntityBuilder
{
public:
    explicit EntityBuilder(ECS::EntityManager& entityManager_) : EntityBuilder(entityManager_, entityManager_.createEntity())
	{
	}

	EntityBuilder(ECS::EntityManager& entityManager_, unsigned entityId_) : entityId(entityId_), entityManager(entityManager_)
	{
	}

	/// <summary>
	/// Adds a component to the entity.
	/// </summary>
	/// <param name="component">The component to add to the entity.</param>
	template <typename T>
	EntityBuilder& addComponent(T&& component)
	{
		entityManager.addComponentToEntity(entityId, component);
		return *this;
	}

	/// <summary>
	/// Adds a component to the entity.
	/// </summary>
	/// <param name"fs">Constructor  parameters for the Component to add</param>
	template <typename T, typename... Fs>
	EntityBuilder& addComponent(Fs ... fs)
	{
		entityManager.addComponentToEntity(entityId, T(std::forward<Fs>(fs)...));
		return *this;
	}

	///	<summary>
	/// Get the id of the entity.
	/// </summary>
	unsigned getEntity() const { return entityId; }

private:
	unsigned entityId{0};
	ECS::EntityManager& entityManager;
};
