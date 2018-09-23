#pragma once

#include "Context.h"

class System
{
public:

	System();

	void virtual update(Context c);

	~System();
};