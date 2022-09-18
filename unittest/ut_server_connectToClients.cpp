// Copyright Vu 2022

#include <gtest/gtest.h>
#include "../src/header/server.h"

Server server;

TEST(connectToCLientTest, succeed) { EXPECT_EQ(0, server.ConnectToClients()); }

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
