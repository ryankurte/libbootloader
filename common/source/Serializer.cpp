
#include "Serializer.hpp"

#include <algorithm>
#include <stdlib.h>

#include "pb_encode.h"
#include "pb_decode.h"
#include "freyja.pb.h"

namespace Freyja
{

int Serializer::CreateProgrammerRequest(uint32_t type, uint32_t serial, uint32_t max_data, Version* v, uint8_t* data, uint8_t max_length)
{
    int length;

    pb_ostream_t ostream = pb_ostream_from_buffer(data, max_length);

    if (!Serializer::CreateBase(&ostream, FreyjaMessage_Type_PROG_REQ)) {
        return -1;
    }

    if (!Serializer::WriteProgrammerRequest(&ostream, type, serial, max_data, v)) {
        return -2;
    }

    return ostream.bytes_written;
}


bool Serializer::CreateBase(pb_ostream_t *ostream, FreyjaMessage_Type type)
{
    FreyjaMessage message = FreyjaMessage_init_zero;

    message.type = type;

    return pb_encode(ostream, FreyjaMessage_fields, &message);
}

bool Serializer::AddSubmessage(pb_ostream_t *ostream, const pb_field_t messagetype[], const void *message)
{
    const pb_field_t *field;
    for (field = FreyjaMessage_fields; field->tag != 0; field++) {
        if (field->ptr == messagetype) {
            /* This is our field, encode the message using it. */
            if (!pb_encode_tag_for_field(ostream, field)) {
                return false;
            }

            return pb_encode_submessage(ostream, messagetype, message);
        }
    }

    return false;
}


bool Serializer::WriteProgrammerRequest(pb_ostream_t *ostream, uint32_t type, uint32_t serial, uint32_t max_size, Version *v)
{
    ProgrammerRequest pr = ProgrammerRequest_init_zero;

    pr.serial = serial;
    pr.type = type;
    pr.max_size = max_size;

    if (v != NULL) {
        pr.has_appVersion = true;
        Serializer::AddAppVersion(&(pr.appVersion), v);
    }

    return Serializer::AddSubmessage(ostream, ProgrammerRequest_fields, &pr);
}

void Serializer::AddAppVersion(AppVersion* av, Version* v)
{
    av->major = v->GetMajor();
    av->minor = v->GetMinor();
    av->patch = v->GetPatch();

    size_t description_len = std::min(sizeof(AppVersion_description_t) - 1 , strlen(v->GetDescription()));
    strncpy((char*)av->description.bytes, v->GetDescription(), description_len);
    av->description.size = description_len;
}

};
