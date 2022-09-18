// Copyright 2022

#ifndef SRC_HEADER_CLIENT_H_
#define SRC_HEADER_CLIENT_H_
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <mutex>  //NOLINT
#include <stdexcept>
#include <string>
#include <thread>  //NOLINT
#include <utility>
#include <vector>
#define MAX_LEN 20000
#define NUM_COLORS 6
#endif  // SRC_HEADER_CLIENT_H_

using std::cin;
using std::cout;
using std::endl;
using std::stoi;
using std::string;
using std::thread;
using std::to_string;
using std::vector;

using std::make_pair;
using std::pair;
const string defCol = "\033[0m";  // NOLINT
const string colors[] = {  // NOLINT
    "\033[31m", "\033[32m", "\033[33m",          // red,green,yello // NOLINT
    "\033[36m", "\033[35m", "\033[34m"};         // cyan,magenta,blue // NOLINT
const string backgroundYellow = "\033[43m";      // NOLINT
const string foregroundBlack = "\033[30m";       // NOLINT
const string backgroundCyan = "\033[46m";        // NOLINT
const string bgRedfgWhite = "\033[41m\033[37m";  // NOLINT
const string bgYellowfgBlack = "\033[43m\033[30m";  // NOLINT

const int maxLenUsername = 20;
const int maxLenPassword = 20;
const int maxLenPress = 1;
const int maxLenRoomId = 10;
const char seperator1 = '~';
const char seperator2 = '`';
const char seperator3 = '#';

class Client {
 private:
  char *server_ip;
  int port, client_socket, status;
  sockaddr_in server_addr;
  thread send_thread;
  thread recv_thread;
  bool exit_flag;  // for communication between thread to exit
  // char name_str[MAX_LEN]; // save username to print 1-1 room and multiple
  // session chat
  string name_str;
  bool have_to_logout;  // when another session delete accout or change password
                        // => true
  bool is_connect_timeout;  // for Console to exit when connection timeout
  char msg_input[MAX_LEN];
  char password_str[MAX_LEN];
  string
      room_name_id;  // room name but name to avoid same name to local variable

 public:
  Client();
  int CreateSocket();
  int ConnectServer();
  int SendMsg();
  int RecvMsg();
  int CreateThread();
  string GetColor(int code);
  int EraseText(int cnt);
  int StopConnection();
  int Login();
  int Console();
  int Register();
  int ChatConsole();
  int PrintChatKeyControl(bool is_empty_input);
  int ModifyConsole();
  int DeleteConfirmConsole();
  int RoomConsole();
  int DeleteConfirmConsole2();
  int CheckAndReconnectServer();
  int ChooseRoomConsole();
  vector<string> Split(string str, char seperator);
  vector<vector<string>> SplitStringRoom(string str);
  int PrintRoomMenu(vector<vector<string>> room);
  bool isValidRoomChoice(const vector<vector<string>> &split_str_room,
                         const string &room_id);
  int CreateRoomConsole();
  int PrintUserMenu(vector<string> user);
  int SendMessage(string message);
  pair<int, string> RecvMessage(int client_socket);
};