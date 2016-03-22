

#pragma once

#include <stdint.h>
#include <stddef.h>

namespace Freyja {

class ISendReceive {
public:
	
	/**
	 * Fetch recieved data up tp max_length
	 * @returns amount of data received, 0 for no data
	 */
	virtual int Receive(uint8_t* data, size_t max_length) = 0;


	virtual int Send(uint8_t* data, size_t length) = 0;
};

}
