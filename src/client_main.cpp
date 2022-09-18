// Copyright 2022

#include "header/client.h"

void ctrlCHandler(int signalNum) {
  signal(SIGINT, ctrlCHandler);
  fflush(stdout);
}
int main(int argc, char *argv[]) {
  Client client;
  signal(SIGINT, ctrlCHandler);
  client.CreateSocket();
  client.ConnectServer();
  client.Console();
  return 0;
}
