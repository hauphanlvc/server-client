#include "../src/header/client.h"
#include <gtest/gtest.h>
Client client("localhost",1234);
TEST (createClientTest, succeed) {
  EXPECT_EQ(0, client.createSocket());
}
TEST(connectToServerTest,succeed) {
  EXPECT_EQ(0, client.connectToServer());
}
TEST(connectToServerTest,unsucceed) {
  EXPECT_EQ(-1, client.connectToServer());
}
int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}