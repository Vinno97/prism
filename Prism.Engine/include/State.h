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
	/// Method to initialize the state
	/// </summary>
	/// <param name="context">Contains context</param>
	virtual void onInit(Context &context);

	/// <summary>
	/// Method to update the state
	/// </summary>
	/// <param name="context">Contains context</param>
	virtual void onUpdate(Context &context) = 0;

	/// <summary>
	/// Method to enter the state
	/// </summary>
	virtual void onEnter(Context & context);

	/// <summary>
	/// Method to leave the state
	/// </summary>
	virtual void onLeave();
};
