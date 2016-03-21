

#pragma once

#include <stdint.h>

class ISendReceive {
	virtual int Put(uint8_t* data, size_t length) = 0;
	virtual int Get(uint8_t* data, size_t* length) = 0;
};
