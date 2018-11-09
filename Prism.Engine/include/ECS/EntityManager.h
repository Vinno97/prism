#pragma once

#include <cstdio>
#include <vector>
#include <map>
#include <typeindex>

#include "Components/Component.h"
#include "Components/PositionComponent.h"

#include "Entity.h"

namespace ECS {

using namespace Components;

/// <summary>
///	Handles the creation, management and removal of Entities.
/// </summary>
class EntityManager {
 public:
  EntityManager();
  ~EntityManager();

  /// <summary>
  /// Creates a new entity.
  /// </summary>
  /// <param name="A">A component to be added to the new entity</param>
  /// <returns>The ID of the newly created entity.</returns>
  template <class A>
  int createEntity(A& c1) {
    addComponentToEntity(lastEntityId, c1);
    return lastEntityId;
  }

  /// <summary>
  /// Creates a new entity.
  /// </summary>
  /// <param name="A">A component to be added to the new entity</param>
  /// <param name="B">A component to be added to the new entity</param>
  /// <returns>The ID of the newly created entity.</returns>
  template <class A, class B>
  int createEntity(A& c1, B& c2) {
    int entity = createEntity(c1);
    addComponentToEntity(entity, c2);
    return entity;
  }

  /// <summary>
  /// Creates a new entity.
  /// </summary>
  /// <param name="A">A component to be added to the new entity</param>
  /// <param name="B">A component to be added to the new entity</param>
  /// <param name="C">A component to be added to the new entity</param>
  /// <returns>The ID of the newly created entity.</returns>
  template <class A, class B, class C>
  int createEntity(A& c1, B& c2, C& c3) {
    int entity = createEntity(c1, c2);
    addComponentToEntity(entity, c3);
    return entity;
  }

  /// <summary>
  /// Creates a new entity.
  /// </summary>
  /// <param name="A">A component to be added to the new entity</param>
  /// <param name="B">A component to be added to the new entity</param>
  /// <param name="C">A component to be added to the new entity</param>
  /// <param name="D">A component to be added to the new entity</param>
  /// <returns>The ID of the newly created entity.</returns>
  template <class A, class B, class C, class D>
  int createEntity(A& c1, B& c2, C& c3, D& c4) {
    int entity = createEntity(c1, c2, c3);
    addComponentToEntity(entity, c4);
    return entity;
  }

  /// <summary>
  /// Creates a new entity.
  /// </summary>
  /// <param name="A">A component to be added to the new entity</param>
  /// <param name="B">A component to be added to the new entity</param>
  /// <param name="C">A component to be added to the new entity</param>
  /// <param name="D">A component to be added to the new entity</param>
  /// <param name="E">A component to be added to the new entity</param>
  /// <returns>The ID of the newly created entity.</returns>
  template <class A, class B, class C, class D, class E>
  int createEntity(A& c1, B& c2, C& c3, D& c4, E& c5) {
    int entity = createEntity(c1, c2, c3, c4);
    addComponentToEntity(entity, c5);
    return entity;
  }

  /// <summary>
  /// Creates a new entity.
  /// </summary>
  /// <param name="A">A component to be added to the new entity</param>
  /// <param name="B">A component to be added to the new entity</param>
  /// <param name="C">A component to be added to the new entity</param>
  /// <param name="D">A component to be added to the new entity</param>
  /// <param name="E">A component to be added to the new entity</param>
  /// <param name="F">A component to be added to the new entity</param>
  /// <returns>The ID of the newly created entity.</returns>
  template <class A, class B, class C, class D, class E, class F, class G>
  int createEntity(A& c1, B& c2, C& c3, D& c4, E& c5, F& c6, G& c7) {
    int entity = createEntity(c1, c2, c3, c4, c5, c6);
    addComponentToEntity(entity, c7);
    return entity;
  }

  /// <summary>
  /// Creates a new entity.
  /// </summary>
  /// <param name="A">A component to be added to the new entity</param>
  /// <param name="B">A component to be added to the new entity</param>
  /// <param name="C">A component to be added to the new entity</param>
  /// <param name="D">A component to be added to the new entity</param>
  /// <param name="E">A component to be added to the new entity</param>
  /// <param name="F">A component to be added to the new entity</param>
  /// <param name="G">A component to be added to the new entity</param>
  /// <returns>The ID of the newly created entity.</returns>
  template <class A,
            class B,
            class C,
            class D,
            class E,
            class F,
            class G,
            class H>
  int createEntity(A& c1, B& c2, C& c3, D& c4, E& c5, F& c6, G& c7, H& c8) {
    int entity = createEntity(c1, c2, c3, c4, c5, c6, c7);
    addComponentToEntity(entity, c8);
    return entity;
  }

  /// <summary>
  /// Creates a new entity.
  /// </summary>
  /// <param name="A">A component to be added to the new entity</param>
  /// <param name="B">A component to be added to the new entity</param>
  /// <param name="C">A component to be added to the new entity</param>
  /// <param name="D">A component to be added to the new entity</param>
  /// <param name="E">A component to be added to the new entity</param>
  /// <param name="F">A component to be added to the new entity</param>
  /// <param name="G">A component to be added to the new entity</param>
  /// <param name="H">A component to be added to the new entity</param>
  /// <returns>The ID of the newly created entity.</returns>
  template <class A,
            class B,
            class C,
            class D,
            class E,
            class F,
            class G,
            class H,
            class I>
  int createEntity(A& c1,
                   B& c2,
                   C& c3,
                   D& c4,
                   E& c5,
                   F& c6,
                   G& c7,
                   H& c8,
                   I& c9) {
    int entity = createEntity(c1, c2, c3, c4, c5, c6, c7, c8);
    addComponentToEntity(entity, c9);
    return entity;
  }

  /// <summary>
  /// Creates a new entity.
  /// </summary>
  /// <param name="A">A component to be added to the new entity</param>
  /// <param name="B">A component to be added to the new entity</param>
  /// <param name="C">A component to be added to the new entity</param>
  /// <param name="D">A component to be added to the new entity</param>
  /// <param name="E">A component to be added to the new entity</param>
  /// <param name="F">A component to be added to the new entity</param>
  /// <param name="G">A component to be added to the new entity</param>
  /// <param name="H">A component to be added to the new entity</param>
  /// <param name="I">A component to be added to the new entity</param>
  /// <returns>The ID of the newly created entity.</returns>
  template <class A,
            class B,
            class C,
            class D,
            class E,
            class F,
            class G,
            class H,
            class I,
            class J>
  int createEntity(A& c1,
                   B& c2,
                   C& c3,
                   D& c4,
                   E& c5,
                   F& c6,
                   G& c7,
                   H& c8,
                   I& c9,
                   J& c10) {
    int entity = createEntity(c1, c2, c3, c4, c5, c6, c7, c8, c9);
    addComponentToEntity(entity, c10);
    return entity;
  }

  /// <summary>
  /// Adds a component to a given entity.
  /// </summary>
  /// <param name="entityId">The ID of the entity to add the component
  /// to.</param> <param name="entityId">The component to add to the
  /// entity.</param>
  template <class T,
            typename = std::enable_if<std::is_base_of<Component, T>::value>>
  void addComponentToEntity(unsigned int entityId, T& component) {
    const std::type_index type = std::type_index(typeid(component));

    if (entityComponents.find(type) != entityComponents.end()) {
      std::map<unsigned int, Component*>* components =
          &entityComponents.at(type);

      if (components->find(entityId) != components->end()) {
        throw std::runtime_error("Already attached a component of type " +
                                 *type.name() + *" to entity " +
                                 std::to_string(entityId));
      }
    }
    entityComponents[type][entityId] = new T(component);
  }

  /// <summary>
  /// Removes a component from a given entiy.
  /// </summary>
  /// <param name="entityId">The ID of the entity to remove the component
  /// from.</param>
  template <typename T,
            typename = std::enable_if<std::is_base_of<Component, T>::value>>
  void removeComponentFromEntity(unsigned int entityId) {
    const std::type_index type{std::type_index(typeid(T))};
    removeComponentFromEntity(entityId, type);
  }

  /// <summary>
  /// Retrieves a compnent from a given entity.
  /// </summary>
  /// <param name="entityId">The ID of the entity to get the component
  /// from.</param> <returns>A pointer to the component belonging to the
  /// entity.</returns>
  template <typename T,
            typename = std::enable_if<std::is_base_of<Component, T>::value>>
  T* getComponent(unsigned int entityId) const {
    const std::type_index type{std::type_index(typeid(T))};
    return static_cast<T*>(getComponent(entityId, type));
  }

  // <summary>
  /// Returns whether or not an entity has a component.
  /// </summary>
  /// <param name="entityId">The ID of the entity to get the component
  /// from.</param> <returns>A boolean indicator whether the entity has the
  /// component.</returns>
  template <typename T,
            typename = std::enable_if<std::is_base_of<Component, T>::value>>
  bool hasComponent(unsigned int entityId) const {
    const std::type_index type{std::type_index(typeid(T))};
    return hasComponent(entityId, type);
  }

  /// <summary>
  /// Retrieves all entities with a certain component type.
  /// </summary>
  /// <returns>A vector containing combinations of entities and the matching
  /// component.</returns>
  template <typename T,
            typename = std::enable_if<std::is_base_of<Component, T>::value>>
  std::vector<Entity<T*>> getAllEntitiesWithComponent() const {
    auto const type = std::type_index(typeid(T));

    auto const entities = getAllEntitiesWithComponent(type);

    std::vector<Entity<T*>> result;

    result.reserve(entities.size());
    for (auto const& entry : entities) {
      Entity<T*> entity;
      entity.id = entry.id;
      entity.component = static_cast<T*>(entry.component);
      result.push_back(entity);
    }
    return result;
  }

  /// <summary>
  /// Removes an entity and its components.
  /// </summary>
  /// <param name="entityId">The ID of the entity to be removed.</param>
  void removeEntity(unsigned int entityId);

 private:
  unsigned int lastEntityId = 0;

  /// <summary>
  /// Keeps a list of all instances of each component type.
  /// </summary>
  std::map<std::type_index, std::map<unsigned int, Component*>>
      entityComponents;

  /// <summary>
  /// Keeps a list of all Listeners attached to the EntityManager.
  /// </summary>

  Component* getComponent(unsigned int entityId,
                          std::type_index componentType) const;

  bool hasComponent(unsigned int entityId, std::type_index componentType) const;

  std::vector<Entity<Component*>> getAllEntitiesWithComponent(
      const std::type_index& componentType) const;

  void removeComponentFromEntity(unsigned int entityId,
                                 std::type_index componentType);
};
}  // namespace ECS