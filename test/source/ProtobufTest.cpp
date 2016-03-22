
#include <iostream>
#include "gtest/gtest.h"

#include "pb_encode.h"
#include "pb_decode.h"
#include "freyja.pb.h"

#include "Serializer.hpp"

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

TEST_F(ProtobufTest, ProgrammerRequestMessageTest)
{
    uint8_t buffer[64];
    FreyjaMessage message = FreyjaMessage_init_zero;

    uint32_t testType = rand();
    uint32_t testSerial = rand();
    uint32_t testMax = 4096;

    int length = Serializer::CreateProgrammerRequest(testType, testSerial, testMax, NULL, buffer, sizeof(buffer));

    pb_istream_t istream = pb_istream_from_buffer(buffer, length);

    bool status = pb_decode(&istream, FreyjaMessage_fields, &message);
    ASSERT_EQ(true, status);

    ASSERT_EQ(FreyjaMessage_Type_PROG_REQ, message.type);

    ASSERT_EQ(testSerial, message.programmerRequest.serial);
    ASSERT_EQ(testType, message.programmerRequest.type);
    ASSERT_EQ(testMax, message.programmerRequest.max_size);
}

TEST_F(ProtobufTest, ProgrammerRequestMessageWithVersion)
{
    uint8_t buffer[64];
    FreyjaMessage message = FreyjaMessage_init_zero;

    uint32_t testType = rand();
    uint32_t testSerial = rand();
    uint32_t testMax = 4096;

    Version v = Version(1, 0, 32, "v1.0.32-dirty");

    int length = Serializer::CreateProgrammerRequest(testType, testSerial, testMax, &v, buffer, sizeof(buffer));

    pb_istream_t istream = pb_istream_from_buffer(buffer, length);

    bool status = pb_decode(&istream, FreyjaMessage_fields, &message);
    ASSERT_EQ(true, status);

    ASSERT_EQ(FreyjaMessage_Type_PROG_REQ, message.type);

    ASSERT_EQ(testSerial, message.programmerRequest.serial);
    ASSERT_EQ(testType, message.programmerRequest.type);
    ASSERT_EQ(testMax, message.programmerRequest.max_size);

    ASSERT_EQ(v.GetMajor(), message.programmerRequest.appVersion.major);
    ASSERT_EQ(v.GetMinor(), message.programmerRequest.appVersion.minor);
    ASSERT_EQ(v.GetPatch(), message.programmerRequest.appVersion.patch);
}
