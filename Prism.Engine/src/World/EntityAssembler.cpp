#include "World/EntityAssembler.h"

namespace World {
	void EntityAssembler::registerAssembler(int objectId, int(*fun)(void)) {
		this->assemblers[objectId] = fun;
	}

	int EntityAssembler::assemble(ObjectProperties object) const {
		return assemblers.at(object.gid)();
	}

}
