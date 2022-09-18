// Copyright 2022

#ifndef SRC_HEADER_SERVER_H_
#define SRC_HEADER_SERVER_H_
#include <arpa/inet.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include "mysql_connection.h"  //NOLINT
#define MAX_LEN 20000
#define NUM_COLORS 6
#define MAX_CLIENTS 200
#endif  // SRC_HEADER_SERVER_H_

using std::map;
using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::to_string;
using std::vector;
using std::make_pair;
using std::pair;

const string defCol = "\033[0m";                               // NOLINT
const string colors[] = {"\033[31m", "\033[32m", "\033[33m",   // NOLINT
                         "\033[34m", "\033[35m", "\033[36m"};  // NOLINT
const char seperator1 = '~';
const char seperator2 = '`';
const string hash = "b8a8407b722856600abb4723f612bad4d04c5929e1a9fc36c4ba3e7d8abe692b";
struct Terminal {
  string username;
  string password;
  int socket;
  int success;
  int stage;
  int menu_id;
  int chat_status;
  string old_password;
  string new_password;
  int room_id;
  int color_id;
  bool need_logout;
};

class Server {
 private:
  // mutex cout_mtx, clients_mtx;
  // vector<Terminal> clients;
  map<int, bool> login_status;
  map<int, string > username_of_client_socket;
  map<int, int> room_id_of_client_socket;
  int server_socket;
  struct pollfd clients_fds[MAX_CLIENTS];

 public:
  Server();
  int CheckLogin(string user_name, string password);
  int ConnectToClients();
  string GetColor(int code);
  // Set name of client
  int SetName(int id, char name[]);
  // Send message
  int SendMessageToClient(string name, string message,
                          int client_socket, int room_id);
  // For synchronisation of cout statements
  int SharedPrint(string str, bool end_line = true);
  // Broadcast message to all clients except the sender
  int BroadcastMessage(string message, int sender_id, int room_id);
  // Broadcast a number to all clients except the sender
  int BroadcastMessage(int num, int sender_id, int room_id);
  int EndConnection(int id);
  int CheckRegister(string user_name);
  int CreateAccount(string user_name, string password);
  int SaveMessage(string user_name, int room_id, string content);
  int LoadMessage(int client_id, int room_id, int day = 2);
  int ModifyName(string user_name, string new_name);
  int ChangePassword(string user_name, string old_password,
                     string new_password);
  int DeleteUser(string user_name);
  int Login(int client_socket, string user_name, string password);
  int Register(int client_socket, string user_name, string password);
  int GetListRoom(string username, string &list);  // NOLINT
  int GetListUser(string username, string &list);  // NOLINT
  int SendListToClient(string flag, string username, int client_id);
  int InitChatOneOne(string user_1, string user_2);
  int InitChatRoom(string room_name, vector<string> members);
  int CreateRoom(int client_socket, string str);
  vector<string> Split(string str, char seperator);
  int GetColorIdByUsername(string user_name);
  int SendExitToClientsByUsername(string username, int client_socket);
  int SendMessage(int client_socket, string message);
  pair<int, string> RecvMessage(int client_socket);
  vector<string> SplitString(string str, string del);
  int GetListUserInside(int room_id, string username, string &list);
  int KickUserFromRoom(int room_id, vector<string> users);
  bool CheckAdmin(string user_name, int room_id);
  bool CheckRoomExisted(string username, int room_id);
  int GetListUserOutSide(int room_id,  string &list);
  int AddUserToRoom(int room_id, vector<string> users);
  int ModifyRoomName(int room_id, string new_name);
};
