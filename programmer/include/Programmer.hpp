
#pragma once

#include <stdint.h>
#include "ISendReceive.hpp"
#include "IProgrammer.hpp"

#include "freyja.pb.h"

namespace Freyja {

class Programmer {
public:
	Programmer(IProgrammer* ip, ISendReceive* sr);
	int Tick();

private:
	int HandleMessage(uint8_t* data, size_t length);
	int HandleProgReq(FreyjaMessage * message);

	IProgrammer* _ip;	//!< Programmer interface implementation
	ISendReceive* _sr;
};

}