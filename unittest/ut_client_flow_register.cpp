// Copyright Khanh 2022

#include <gtest/gtest.h>
#include <sys/ioctl.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "../src/header/client.h"
void gotoxyt(int x, int y) { printf("%c[%d;%df", 0x1B, y, x); }

using std::cin;
using std::istringstream;

Client client;

TEST(exit_register_username, succeed) {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  int height = w.ws_row;
  // system("clear");
  gotoxyt(1, height);
  client.CreateSocket();
  client.ConnectServer();
  // istringstream iss("#exit\n");
  // cin.rdbuf(iss.rdbuf());
  EXPECT_EQ(1, client.Register());
  gotoxyt(1, height);
}
TEST(exit_register_password, succeed) {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  int height = w.ws_row;
  // system("clear");
  gotoxyt(1, height);
  // client.CreateSocket();
  // client.ConnectServer();
  // istringstream iss("#exit\n");
  // cin.rdbuf(iss.rdbuf());
  EXPECT_EQ(1, client.Register());
  gotoxyt(1, height);
}
TEST(register_flow, succeed) {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  int height = w.ws_row;
  // system("clear");
  gotoxyt(1, height);
  // client.CreateSocket();
  // client.ConnectServer();
  // istringstream iss("#exit\n");
  // cin.rdbuf(iss.rdbuf());
  EXPECT_EQ(0, client.Register());
  gotoxyt(1, height);
}
TEST(register_flow, fail) {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  int height = w.ws_row;
  // system("clear");
  gotoxyt(1, height);
  // client.CreateSocket();
  // client.ConnectServer();
  // istringstream iss("#exit\n");
  // cin.rdbuf(iss.rdbuf());
  EXPECT_EQ(-1, client.Register());
  gotoxyt(1, height);
}
TEST(exit_login_username, succeed) {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  int height = w.ws_row;
  // system("clear");
  gotoxyt(1, height);
  client.CreateSocket();
  client.ConnectServer();
  // istringstream iss("#exit\n");
  // cin.rdbuf(iss.rdbuf());
  EXPECT_EQ(1, client.Login());
  gotoxyt(1, height);
}
TEST(exit_login_password, succeed) {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  int height = w.ws_row;
  // system("clear");
  gotoxyt(1, height);
  // client.CreateSocket();
  // client.ConnectServer();
  // istringstream iss("#exit\n");
  // cin.rdbuf(iss.rdbuf());
  EXPECT_EQ(1, client.Login());
  gotoxyt(1, height);
}

int main(int argc, char **argv) {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  int height = w.ws_row;
  gotoxyt(1, height);
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
