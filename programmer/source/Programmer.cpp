
#include "Programmer.hpp"

#include <stdlib.h>
#include <iostream>

#include <pb_encode.h>
#include <pb_decode.h>

#include "freyja.pb.h"

namespace Freyja
{

Programmer::Programmer(IProgrammer* ip, ISendReceive* sr)
{
    //Save interfaces for internal use
    _ip = ip;
    _sr = sr;
}

int Programmer::Tick()
{
	uint8_t receive_buffer[64];
	size_t length;
	int res = 0;

	//Check for available messages
	length = this->_sr->Receive(receive_buffer, sizeof(receive_buffer));
	std::cout << length << std::endl;
	if(length > 0) {
		res = this->HandleMessage(receive_buffer, length);
	}

    return res;
}

int Programmer::HandleMessage(uint8_t* data, size_t length)
{
	int res = 0;

    //Parse protobuf
    pb_istream_t stream = pb_istream_from_buffer(data, length);

    FreyjaMessage message = FreyjaMessage_init_zero;

    bool status = pb_decode(&stream, FreyjaMessage_fields, &message);

    if (!status) {
        //Protobuf parsing error
         std::cout << "Protobuf parsing error" << std::endl;
        return -1;
    }

    std::cout << "Received message type: " << message.type << std::endl;

    switch (message.type) {
    case FreyjaMessage_Type_PROG_REQ:
        res = HandleProgReq(&message);
        break;
    case FreyjaMessage_Type_PROG_RESP:

        break;
    case FreyjaMessage_Type_DATA_REQ:

        break;
    case FreyjaMessage_Type_DATA_RESP:

        break;
    case FreyjaMessage_Type_PROG_RES:

        break;
    default:
    	std::cout << "Unrecognized message type: " << message.type << std::endl;
    }	


    return res;
}

int Programmer::HandleProgReq(FreyjaMessage* message)
{
    uint8_t response_buffer[64];
    bool status;
    FreyjaMessage response = FreyjaMessage_init_zero;

    std::cout << "Received programmer request" << std::endl;

    //Create output stream
    pb_ostream_t stream = pb_ostream_from_buffer(response_buffer, sizeof(response_buffer));

    //Attempt to load an application
    uint32_t type = message->programmerRequest.type;
    uint32_t serial = message->programmerRequest.serial;
    Application* app = this->_ip->LocateBinary(type, serial);

    if (app == NULL) {
        //Build response
        response.type = FreyjaMessage_Type_PROG_RESP;
        response.programmerResponse.canProgram = false;

        bool status = pb_encode(&stream, FreyjaMessage_fields, &response);
        if (!status) {
            //Encoding error
            return -1;
        }

    } else {
        response.type = FreyjaMessage_Type_PROG_RESP;
        response.programmerResponse.canProgram = true;

        response.programmerResponse.size = 1;
        response.programmerResponse.crc = 0;

        bool status = pb_encode(&stream, FreyjaMessage_fields, &response);
        if (!status) {
            //Encoding error
            return -1;
        }

        // Write version if required
        Version* v = app->GetVersion();
        if (v != NULL) {
            AppVersion vm = AppVersion_init_zero;

            vm.major = v->GetMajor();
            vm.minor = v->GetMinor();
            vm.patch = v->GetPatch();

            size_t version_len = std::min(sizeof(AppVersion_description_t) - 1 , strlen(v->GetDescription()));

            strncpy((char*)vm.description.bytes, v->GetDescription(), version_len);
            vm.description.size = version_len;

            status = pb_encode_submessage(&stream, AppVersion_fields, &vm);
            if (!status) {
                //Encoding error
                return -1;
            }
        }
    }

    size_t length = stream.bytes_written;
    this->_sr->Send(response_buffer, length);

    return 0;
}



}

