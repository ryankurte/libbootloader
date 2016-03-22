
#pragma once

#include <stdint.h>

#include "pb_encode.h"
#include "pb_decode.h"
#include "freyja.pb.h"

#include "Version.hpp"

namespace Freyja {

class Serializer {
	
public:

	//Create a programmer request message
	static int CreateProgrammerRequest(uint32_t type, uint32_t serial, uint32_t max_data, Version* v, uint8_t* data, uint8_t max_length);

	//Create a programmer response method
	static int CreateProgrammerResponse(uint32_t size, uint32_t crc, Version *v, uint8_t *data, uint8_t max_length);

	// Create a base message
	static bool CreateBase(pb_ostream_t *stream, FreyjaMessage_Type type);

	// Helper to add submessages to base messages
	static bool AddSubmessage(pb_ostream_t *stream, const pb_field_t messagetype[], const void *message);

	// Helper to write an app version submessage
	static void AddAppVersion(AppVersion* av, Version* v);

	// Helper to write an app programmer request submessage
	static bool WriteProgrammerRequest(pb_ostream_t *ostream, uint32_t type, uint32_t serial, uint32_t max_size, Version* v);

};

}
