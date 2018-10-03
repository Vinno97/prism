#pragma once
#include "State.h"
#include <map>
#include <list>
#include <typeindex>

class StateMachine {
 public:
  StateMachine();
  ~StateMachine();

  template <class T,
            typename = std::enable_if<std::is_base_of<State, T>::value>>
  void setState() {
    const std::type_index type{std::type_index(typeid(T))};
    setState(type);
  }

  template <class T>
  void addState(T& state) {
    const std::type_index type{std::type_index(typeid(T))};

    if (hasState(type)) {
      throw std::runtime_error("There can only one type of " + *type.name() +
                               *" registered");
    }

    existingStates[type] = new T(state);
  }

  template <typename T,
            typename = std::enable_if<std::is_base_of<State, T>::value>>
  T* getState() const {
    const std::type_index type{std::type_index(typeid(T))};
    return static_cast<T*>(getState(type));
  }

  template <class T>
  bool hasState() const {
    const std::type_index type{std::type_index(typeid(T))};
    return hasState(type);
  }

  State* getCurrentState();

 private:
  State* currentState;

  // keeps a list of States
  std::map<std::type_index, State*> existingStates;

  void setState(std::type_index type);

  State* getState(std::type_index type) const;
  bool hasState(std::type_index type) const;
};
