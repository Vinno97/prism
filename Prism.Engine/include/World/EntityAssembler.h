#pragma once

#include <map>
#include "ObjectProperties.h"

namespace World {
	class EntityAssembler {
	public:
		EntityAssembler() = default;

		void registerAssembler(int objectId, int(*fun)(void));

		int assemble(ObjectProperties object) const;

	private:
		std::map<int, int(*)(void)> assemblers;
		std::map<int, int> assemblers2;
	};
}
