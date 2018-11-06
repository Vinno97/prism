#pragma once
#include "Context.h"

/// <summary>
/// Abstract State class
/// </summary>
class State {
public:
	State();
	virtual ~State();

	/// <summary>
	/// Method to update the game
	/// </summary>
	/// <param name="context">Contains context</param>
	virtual void onUpdate(Context &context) = 0;

	/// <summary>
	/// Method to initialize the state
	/// </summary>
	virtual void onEnter();

	/// <summary>
	/// Method to leave the state
	/// </summary>
	virtual void onLeave();
};
