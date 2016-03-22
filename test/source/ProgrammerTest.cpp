
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
	ASSERT_EQ(0, 0);

}
