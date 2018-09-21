#pragma once

#include <type_traits>
#include "ECS/Components/Component.h"

namespace ECS {
	using namespace Components;

	//template<class T>
	template<typename T, typename = std::enable_if < std::is_base_of<Component, T>::value>>
	struct EntityWithComponent {
		unsigned int id;
		T component;
	};
}