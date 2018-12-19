#include "State.h"

void State::init(Context &context) {
    onInit(context);
    isInitialized_ = true;
}

void State::enter(Context &context) {
    onEnter(context);
    isActive_ = true;
}

void State::update(Context &context) {
    onUpdate(context);
}

void State::leave(Context &context) {
    onLeave(context);
    isActive_ = false;
}

void State::destroy(Context &context) {
    onDestroy(context);
    isDestroyed_ = true;
}