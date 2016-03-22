
#pragma once

#include "Application.hpp"

namespace Freyja {

class IProgrammer{
public:
	//Find and create an instance of an application for programming
	virtual Application* LocateBinary(uint64_t type, uint64_t serial) = 0;
};

}
