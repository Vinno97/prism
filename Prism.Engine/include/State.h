#pragma once

#include "Context.h"

/// <summary>
/// Abstract State class
/// </summary>
class State {
public:
    State() = default;

    virtual ~State() = default;

    const bool isActive() { return isActive_; }

    const bool isInitialized() { return isInitialized_; }

    const bool isDestroyed() { return isDestroyed_; }

    void init(Context &context);

    void update(Context &context);

    void enter(Context &context);

    void leave(Context &context);

    void destroy(Context &context);

protected:
    /// <summary>
    /// Method to initialize the state
    /// </summary>
    /// <param name="context">Contains context</param>
    virtual void onInit(Context &context) {};

    /// <summary>
    /// Method to update the state
    /// </summary>
    /// <param name="context">Contains context</param>
    virtual void onUpdate(Context &context) = 0;

    /// <summary>
    /// Method to enter the state
    /// </summary>
    virtual void onEnter(Context &context) {}

    /// <summary>
    /// Method to leave the state
    /// </summary>
    virtual void onLeave(Context &context) {};

    /// <summary>
    /// Method destroy the state
    /// </summary>
    virtual void onDestroy(Context &context) {};

private:
    bool isInitialized_{false};
    bool isActive_{false};
    bool isDestroyed_{false};
};
