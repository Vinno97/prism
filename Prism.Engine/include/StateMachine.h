#pragma once
#include <memory>
#include <map>
#include <list>
#include <typeindex>
#include <algorithm>

#include "State.h"


/// <summary>
/// Statemachine class is repsonsible to add and managing the existing states 
/// </summary>
class StateMachine
{
public:
	StateMachine();
	~StateMachine() = default;

	/// <summary>
	/// Set currentSate
	/// </summary>
	template<class T, typename = std::enable_if_t < std::is_base_of<State, T>::type::value>>
	void setState(Context &context)
	{
		const std::type_index type{ std::type_index(typeid(T)) };
		setState(type, context);
	}

	/// <summary>
	/// Remove state
	/// </summary>
	template<class T, typename = std::enable_if_t < std::is_base_of<State, T>::type::value>>
	void removeState()
	{
		const std::type_index type{ std::type_index(typeid(T)) };

		if (hasState(type)) {
			const auto it = existingStates.find(type);
			eolQueue.push_back( std::move((*it).second) );
			existingStates.erase(it);

//			const auto test = existingStates.erase(type);
//			eolQueue.push_back(std::move(test));
		}
	}

	/// <summary>
	/// Add state to list of existing states
	/// </summary>
	/// <param name="context">The context</param>
	///<param name="fs">Constructor parameters for State</param>

	template<typename T, typename...Fs, typename = std::enable_if_t < std::is_base_of<State, T>::type::value>>
	void addState(Context & context, Fs&&... fs )
	{
		const std::type_index type{ std::type_index(typeid(T)) };

		if (hasState(type)) {
			throw std::runtime_error("There can only one type of " + *type.name() + *" registered");
		}
		existingStates[type] = std::make_unique<T>(std::forward<Fs>(fs)...);
	}

	/// <summary>
	/// Get specific state
	/// </summary>
	/// <returns>Returns state </returns>
	template<typename T, typename = std::enable_if_t < std::is_base_of<State, T>::type::value>>
	T* getState() const {
		const std::type_index type{ std::type_index(typeid(T)) };
		return static_cast<T*>(getState(type));
	}

	/// <summary>
	/// Check if state exist in list of existing states
	/// </summary>
	/// <returns>Returns boolean</returns>
	template<class T>
	bool hasState() const {
		const std::type_index type{ std::type_index(typeid(T)) };
		return hasState(type);
	}

	bool hasState(const State& state) const;

	std::vector<State*> getAllStates() const;

	void destroyEolStates(Context& context);

	/// <summary>
	/// Get current state
	/// </summary>
	/// <returns>Returns the current state </returns>
	State *getCurrentState() const;

private:
	State *currentState;
	// keeps a list of States
	std::map<std::type_index, std::unique_ptr<State>> existingStates;

	std::vector<std::unique_ptr<State>> eolQueue;

	void setState(std::type_index type, Context &context);

	State* getState(std::type_index type) const;
	bool hasState(std::type_index type) const;
};


