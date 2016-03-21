
#include <iostream>

#include "gtest/gtest.h"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  int res = RUN_ALL_TESTS();

  //std::cin.ignore();

  return res;
}
