#pragma once

#include <type_traits>
#include "ECS/Components/Component.h"

namespace ECS
{
	template <typename T, typename = std::enable_if<std::is_base_of<Components::Component, T>::value>>
	struct Entity
	{
		unsigned int id;
		T component;
	};
}
