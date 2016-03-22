

#pragma once

#include <stdint.h>
#include <stddef.h>

namespace Freyja {

class IReaderWriter {
	virtual int Read(uint8_t* data, size_t length) = 0;
	virtual int Write(uint8_t* data, size_t length) = 0;
};

}
