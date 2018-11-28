#include "Menu/ControlBuilder.h"


namespace Menu {
	ControlBuilder::ControlBuilder()
	{
	}

	Control ControlBuilder::buildControl() {
		return Control{ control };
	}

	void ControlBuilder::setClickCallback(std::function<void()> callback) {

	}

	void ControlBuilder::setEnterCallback(std::function<void(Math::Vector3f&position, Math::Vector3f&size)> callback) {

	}

	void ControlBuilder::setLeaveCallback(std::function<void(Math::Vector3f&position, Math::Vector3f&size)> callback) {

	}

	void ControlBuilder::setTexture(const char *path) {

	}

	ControlBuilder::~ControlBuilder()
	{
	}
}