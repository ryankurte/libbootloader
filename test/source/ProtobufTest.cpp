
#include <iostream>
#include "gtest/gtest.h"

#include "Serializer.hpp"

#include "pb_encode.h"
#include "pb_decode.h"
#include "freyja.pb.h"

using namespace Freyja;

class ProtobufTest : public ::testing::Test
{
public:
    void SetUp() {};
    void TearDown() {};

protected:

};


TEST_F(ProtobufTest, MessageTypeTest)
{
	uint8_t buffer[64];
    FreyjaMessage message = FreyjaMessage_init_zero;

    pb_ostream_t ostream = pb_ostream_from_buffer(buffer, sizeof(buffer));

    message.type = FreyjaMessage_Type_PROG_REQ;

    bool status = pb_encode(&ostream, FreyjaMessage_fields, &message);
    ASSERT_EQ(true, status);

    int length = ostream.bytes_written;

    pb_istream_t istream = pb_istream_from_buffer(buffer, length);

    status = pb_decode(&istream, FreyjaMessage_fields, &message);
    ASSERT_EQ(true, status);

    ASSERT_EQ(FreyjaMessage_Type_PROG_REQ, message.type);
}

TEST_F(ProtobufTest, RequestMessageTest)
{
    uint8_t buffer[64];
    FreyjaMessage message = FreyjaMessage_init_zero;

    pb_ostream_t ostream = pb_ostream_from_buffer(buffer, sizeof(buffer));

    message.type = FreyjaMessage_Type_PROG_REQ;

    bool status = pb_encode(&ostream, FreyjaMessage_fields, &message);
    ASSERT_EQ(true, status);

    ProgrammerRequest rm = ProgrammerRequest_init_zero;
    rm.serial = 0xbeef;
    rm.type = 0xcafe;

    Serializer::AddSubfield(&ostream, ProgrammerRequest_fields, &rm);

    int length = ostream.bytes_written;

    pb_istream_t istream = pb_istream_from_buffer(buffer, length);

    status = pb_decode(&istream, FreyjaMessage_fields, &message);
    ASSERT_EQ(true, status);

    ASSERT_EQ(FreyjaMessage_Type_PROG_REQ, message.type);

    ASSERT_EQ(0xbeef, message.programmerRequest.serial);
    ASSERT_EQ(0xcafe, message.programmerRequest.type);
}
