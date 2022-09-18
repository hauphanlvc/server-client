// Copyright Luan 2022

#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include <string>
#include "../src/header/client.h"

using std::cin;
using std::istringstream;

Client client("localhost", 1111);

TEST(sendNameTest, succedd) {
  istringstream iss("pass");
  cin.rdbuf(iss.rdbuf());
  // This line actually sets cin's input buffer
  // to the same one as used in iss (namely the
  // string data that was used to initialize it)
  EXPECT_EQ(0, client.SendName());
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
