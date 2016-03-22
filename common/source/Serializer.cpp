
#include "Serializer.hpp"

#include <algorithm>
#include <stdlib.h>

#include "pb_encode.h"
#include "pb_decode.h"
#include "freyja.pb.h"

namespace Freyja
{

int Serializer::CreateProgrammerRequest(uint32_t type, uint32_t serial, uint8_t* data, uint8_t max_length)
{
	int length;

	pb_ostream_t ostream = pb_ostream_from_buffer(data, max_length);

	Serializer::CreateBase(&ostream, FreyjaMessage_Type_PROG_REQ);

	Serializer::WriteProgrammerRequest(&ostream, type, serial);

	return ostream.bytes_written;
}


bool Serializer::CreateBase(pb_ostream_t *ostream, FreyjaMessage_Type type)
{
    FreyjaMessage message = FreyjaMessage_init_zero;

    message.type = type;

    return pb_encode(ostream, FreyjaMessage_fields, &message);
}

bool Serializer::AddSubfield(pb_ostream_t *ostream, const pb_field_t messagetype[], const void *message)
{

    const pb_field_t *field;
    for (field = FreyjaMessage_fields; field->tag != 0; field++) {
        if (field->ptr == messagetype) {
            /* This is our field, encode the message using it. */
            if (!pb_encode_tag_for_field(ostream, field)) {
                return false;
            }

            return pb_encode_submessage(ostream, messagetype, &message);
        }
    }

    return false;
}


bool Serializer::WriteProgrammerRequest(pb_ostream_t *ostream, uint32_t type, uint32_t serial)
{
	ProgrammerRequest pr = ProgrammerRequest_init_zero;
    pr.serial = serial;
    pr.type = type;

    return Serializer::AddSubfield(ostream, ProgrammerRequest_fields, &pr);
}

bool Serializer::WriteAppVersion(pb_ostream_t *ostream, Version* v)
{
	AppVersion av = AppVersion_init_zero;
    AppVersion vm = AppVersion_init_zero;

    vm.major = v->GetMajor();
    vm.minor = v->GetMinor();
    vm.patch = v->GetPatch();

    size_t version_len = std::min(sizeof(AppVersion_description_t) - 1 , strlen(v->GetDescription()));

    strncpy((char*)vm.description.bytes, v->GetDescription(), version_len);
    vm.description.size = version_len;

    return Serializer::AddSubfield(ostream, AppVersion_fields, &vm);
}

};
