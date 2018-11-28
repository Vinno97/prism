#include "Menu/Control.h"
#include "Math/Vector3f.h"
#include <functional>

namespace Menu {
#pragma once
	class ControlBuilder
	{
	public:
		ControlBuilder();

		Control buildControl();
		void setClickCallback(std::function<void()> callback));
		void setLeaveCallback(std::function<void(Math::Vector3f&position, Math::Vector3f&size)> callback);
		void setEnterCallback(std::function<void(Math::Vector3f&position, Math::Vector3f&size)> callback);
		void setTexture(const char *path);

		~ControlBuilder();
	private:
		Control control;
	};
}