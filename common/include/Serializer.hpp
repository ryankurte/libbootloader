
#pragma once

#include <stdint.h>

#include "pb_encode.h"
#include "pb_decode.h"
#include "freyja.pb.h"

#include "Version.hpp"

namespace Freyja {

class Serializer {
	
public:

	int CreateProgrammerRequest(uint32_t type, uint32_t serial, uint8_t* data, uint8_t max_length);

	// Create a base message
	static bool CreateBase(pb_ostream_t *stream, FreyjaMessage_Type type);

	// Helper to assist with packing structures
	static bool AddSubfield(pb_ostream_t *stream, const pb_field_t messagetype[], const void *message);

	// Helper to write an app version submessage
	static bool WriteAppVersion(pb_ostream_t *ostream, Version* v);

	// Helper to write an app programmer request submessage
	static bool WriteProgrammerRequest(pb_ostream_t *ostream, uint32_t type, uint32_t serial);

};

}
