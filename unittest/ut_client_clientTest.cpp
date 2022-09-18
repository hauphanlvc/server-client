// Copyright Khanh 2022

#include <gtest/gtest.h>
#include "../src/header/client.h"

Client client("localhost", 1234);

TEST(createClientTest, succeed) { EXPECT_TRUE(client.CreateSocket()); }

// TEST(ConnectServerTest,succeed) {
//    EXPECT_EQ(0, client.ConnectServer());
// }

TEST(ConnectServerTest, unsucceed) { EXPECT_EQ(-1, client.ConnectServer()); }

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
