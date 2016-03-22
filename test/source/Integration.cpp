
#include <iostream>
#include "gtest/gtest.h"

#include "Programmer.hpp"
#include "Bootloader.hpp"

using namespace Freyja;

class FreyjaIntegrationTest : public ::testing::Test
{
public:
    virtual void SetUp() {}
    virtual void TearDown() {}

private:

};


TEST_F(FreyjaIntegrationTest, fake)
{
    EXPECT_EQ(1, 1);
}
