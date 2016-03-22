
#include <iostream>
#include "gtest/gtest.h"

#include "Programmer.hpp"
#include "MockSendReceive.hpp"
#include "IProgrammer.hpp"
#include "Application.hpp"

#include "pb_encode.h"
#include "pb_decode.h"
#include "freyja.pb.h"

#define TEST_TYPE		43

class MockProgrammerInterface: public Freyja::IProgrammer
{
public:
    Freyja::Application* LocateBinary(uint64_t type, uint64_t serial)
    {

        if (type != TEST_TYPE) {
            return NULL;
        }

        uint8_t appBin[4096];
        for (int i = 0; i < sizeof(appBin); i++) {
            appBin[i] = rand();
        }

        Freyja::Application *app = new Freyja::Application(0, 1, 14, "v0.1.14-g12bfbfs", appBin, sizeof(appBin));

        return app;
    }
};

class ProgrammerTest : public ::testing::Test
{
public:
    ProgrammerTest() : p(&mockProgrammer, &mockSendReceive)
    {

    }
    void SetUp()
    {

    }
    void TearDown()
    {

    }

protected:
    Freyja::Programmer p;

    MockProgrammerInterface mockProgrammer;
    MockSendReceive mockSendReceive;
};


TEST_F(ProgrammerTest, ProgrammerRequestDenied)
{
	uint8_t output[64];
    FreyjaMessage message = FreyjaMessage_init_zero;

    pb_ostream_t stream = pb_ostream_from_buffer(output, sizeof(output));

    message.type = FreyjaMessage_Type_PROG_REQ;

    bool status = pb_encode(&stream, FreyjaMessage_fields, &message);
    ASSERT_EQ(true, status);

    ProgrammerRequest pr = ProgrammerRequest_init_zero;
    pr.serial = 1;
    pr.type = 2;
    pr.max_size = 1024 * 16;

    status = pb_encode_submessage(&stream, ProgrammerRequest_fields, &pr);
    ASSERT_EQ(true, status);

    mockSendReceive.PutReceive(output, stream.bytes_written);

    p.Tick();

}
