// Copyright 2022

#include "header/client.h"
#include "header/utils.h"

Client::Client() {
  // set default server ip, server port
  this->server_ip = const_cast<char *>("localhost");
  this->port = 1234;

  // use server ip, server port env if exists
  char *server_ip_char = getenv("SERVER_IP");
  char *server_port_char = getenv("SERVER_PORT");
  if (server_ip_char) this->server_ip = server_ip_char;
  if (server_port_char) this->port = atoi(server_port_char);
  this->is_connect_timeout = false;
  this->room_name_id = "";
}

int Client::CreateSocket() {
  if ((this->client_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket error");
    return -1;
  }
  // fcntl(client_socket, F_SETFL, O_NONBLOCK);
  struct hostent *host = gethostbyname(this->server_ip);
  bzero(reinterpret_cast<char *>(&this->server_addr),
        sizeof(this->server_addr));
  this->server_addr.sin_family = AF_INET;
  this->server_addr.sin_port = htons(this->port);  // Port no. of server
  this->server_addr.sin_addr.s_addr =
      inet_addr(inet_ntoa(*(struct in_addr *)*host->h_addr_list));
  // server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
  // Provide IP address of server
  bzero(&this->server_addr.sin_zero, 0);
  this->exit_flag = false;
}

// for reconnection, unuse for now
int Client::CheckAndReconnectServer() {
  int error_code;
  socklen_t error_code_size = sizeof(error_code);
  getsockopt(client_socket, SOL_SOCKET, SO_ERROR, &error_code,
             &error_code_size);
  if (error_code == EPIPE) {
    Client::ConnectServer();
  }
}

int Client::ConnectServer() {
  int sock = connect(this->client_socket, (struct sockaddr *)&this->server_addr,
                     sizeof(struct sockaddr_in));
  int count = 0;
  while (sock == -1) {
    sock = connect(this->client_socket, (struct sockaddr *)&this->server_addr,
                   sizeof(struct sockaddr_in));
    if (count == 60) {
      cout << "\nTimeout\n";
      this->is_connect_timeout = true;
      StopConnection();
      return -1;
    }
    // reconnecting animation
    string recon_msg = "Connection Error. Reconnecting";
    // number of dots in recon_msg
    int recon_dot_cnt = (recon_dot_cnt + 1) % 5;
    string dot_str(recon_dot_cnt, '.');
    string space_str(5 - recon_dot_cnt, ' ');
    string combine_str = dot_str + space_str;
    cout << recon_msg << combine_str;
    fflush(stdout);
    int erase_len = static_cast<int>(recon_msg.length()) +
                    static_cast<int>(combine_str.length());
    EraseText(erase_len);
    sleep(1);
    count++;
  }
  return 0;
}

int Client::PrintChatKeyControl(bool is_empty_input) {
  int height, width;
  GetScreenSize(width, height);
  const string f4KeyCtrl = "F4: Back";
  const int x_padding_int = 1;
  const string x_padding_str(x_padding_int, ' ');
  gotoxy(1, 2);
  cout << string(width, ' ');
  gotoxy(1, 3);
  cout << string(width, ' ');
  gotoxy(1, 4);
  cout << x_padding_str
       << foregroundBlack + backgroundCyan + this->room_name_id + defCol
       << string(width - 2 * x_padding_int - f4KeyCtrl.size() -
                     this->room_name_id.size(),
                 ' ')
       << foregroundBlack + backgroundYellow + f4KeyCtrl + defCol
       << x_padding_str;

  gotoxy(1, 5);
  cout << string(width, ' ');
  if (!is_empty_input)
    gotoxy(6 + strlen(this->msg_input), height);
  else
    gotoxy(6 + strlen(this->msg_input), height - 1);
}

// Send message to everyone
int Client::SendMsg() {
  bool is_empty_input = false;
  string input;
  while (1) {
    memset(this->msg_input, 0, MAX_LEN);
    if (this->exit_flag || this->have_to_logout) return 0;
    PrintChatKeyControl(is_empty_input);
    if (!is_empty_input)
      cout << colors[1] << "\n\nYou: " << defCol;
    else
      cout << colors[1] << "\nYou: " << defCol;
    fflush(stdin);
    input = Input(true, 1, MAX_LEN - 1, false, &this->msg_input);
    while (input == "#F1" || input == "#F2" || input == "#F3") {
      input = Input(true, 1, MAX_LEN - 1, false, &this->msg_input);
      continue;
    }
    if (strlen(this->msg_input) > 0) {
      if (strcmp(this->msg_input, "#exit") == 0) {
        SendMessage("#exit_chat");
        this->exit_flag = true;
        this->room_name_id = "";
        this->send_thread.detach();
        this->recv_thread.detach();
        return 0;
      }
      SendMessage(this->msg_input);
      is_empty_input = false;
    } else {
      is_empty_input = true;
      // cout << string(5, '\b') << string(5, ' ') << string(5, '\b');
    }
  }
  // cout << "Stop SendMSg" << endl;
}

// Receive message
int Client::RecvMsg() {
  while (1) {
    if (this->exit_flag) {
      return 0;
    }
    string username, str;
    int color_code;
    PrintChatKeyControl(false);
    auto result = RecvMessage(this->client_socket);
    int recv_bytes = result.first;
    str = result.second;
    if (str == "#exit") {
      this->exit_flag = false;
      this->have_to_logout = true;
      return 0;
    }
    if (str == "#exit_chat") {
      this->exit_flag = false;
      return 0;
    }
    if (recv_bytes == 0) {
      gotoxy(1, 1);
      cout << "Connecting" + string(rand() % 3 + 1, '.');  // NOLINT
      continue;
    }
    if (recv_bytes < 0) {
      StopConnection();
      exit(1);
    }
    int len = strlen("You: ") + strlen(this->msg_input);
    string backspace_str = string(len, '\b');
    string space_str = string(len, ' ');
    cout << backspace_str << space_str << backspace_str;
    cout << str << endl;
    cout << colors[1] << "\nYou: " << defCol;
    cout << this->msg_input;
    fflush(stdout);
  }
}

int Client::CreateThread() {
  thread t1(&Client::SendMsg, this);
  thread t2(&Client::RecvMsg, this);
  this->send_thread = move(t1);
  this->recv_thread = move(t2);
  if (this->send_thread.joinable()) this->send_thread.join();
  if (this->recv_thread.joinable()) this->recv_thread.join();
  return 0;
}

string Client::GetColor(int code) { return colors[code % NUM_COLORS]; }

// Erase text from terminal
int Client::EraseText(int cnt) {
  char back_space = 8;
  for (int i = 0; i < cnt; i++) {
    cout << back_space;
  }
}

int Client::StopConnection() {
  SendMessage("#exit");
  this->exit_flag = true;
  this->send_thread.detach();
  this->recv_thread.detach();
  close(this->client_socket);
}

int Client::Login() {
  char exit_login[MAX_LEN] = "#exit_login";  // NOLINT
  SendMessage("2");  // send to server for server to set stage to login
                     // stage for this client
  bool is_login_failed = false;
  while (1) {
    // print login menu
    system("clear");
    gotoxy(1, 1);
    for (int i = 0; i < 33; i++) {
      cout << "-";
    }
    cout << defCol << "\n|" << bgYellowfgBlack
         << "         Login Form            " << defCol << "|\n";
    for (int i = 0; i < 33; i++) {
      cout << "-";
    }
    cout << endl;
    cout << defCol << "|" << colors[1]
         << "Username:                      " << defCol << "|\n";
    cout << "|                               |\n";
    cout << defCol << "|" << colors[2]
         << "Password:                      " << defCol << "|\n";
    cout << "|                               |\n";
    cout << defCol << "|" << colors[4] << "F4. Back                       "
         << defCol << "|\n";
    for (int i = 0; i < 33; i++) {
      cout << "-";
    }
    cout << endl;
    // end print login menu
    if (is_login_failed) {
      cout << "Wrong username or password or account does not exists";
      is_login_failed = false;
    }
    string username, password;
    string check;
    gotoxy(12, 4);
    username = Input(false, 1, maxLenUsername, false);
    while (username.size() == 0 || username == "#F1" || username == "#F2" ||
           username == "#F3") {
      if (username.size() == 0) {
        gotoxy(1, 10);
        cout << "Username can't be empty!" << endl;
        gotoxy(12, 4);
        cout << string(maxLenUsername, ' ');
        gotoxy(12, 4);
      }
      username = Input(false, 1, maxLenUsername, false);
    }

    if (username == "#exit") {
      SendMessage("#exit_login");
      return 1;  // 1 for user exit
    }
    name_str = username;
    SendMessage(username);
    gotoxy(12, 6);
    password = Input(false, 0, maxLenPassword, false);
    while (password.size() == 0 || password == "#F1" || password == "#F2" ||
           password == "#F3") {
      if (password.size() == 0) {
        gotoxy(1, 10);
        cout << "Password can't be empty!" << endl;
        gotoxy(12, 6);
        cout << string(maxLenPassword, ' ');
        gotoxy(12, 6);
      }
      password = Input(false, 0, maxLenPassword, false);
    }

    if (password == "#exit") {
      SendMessage("#exit_login");
      return 1;  // 1 for user exit
    }
    memset(this->password_str, 0, sizeof(this->password_str));
    strcpy(this->password_str, password.c_str());  // NOLINT
    SendMessage(password);
    check = RecvMessage(this->client_socket).second;
    system("clear");
    if (check == "#login_fail") {
      is_login_failed = true;
    } else if (check == "#login_success") {
      is_login_failed = false;
      return 0;
    }
  }
}
int Client::Console() {
  if (this->is_connect_timeout) return -1;
  // store input key
  string press;
  bool is_invalid_press = false;
  // flag to print register result
  // -2 init (print nothing)
  // -1 register fail
  //  0 register success
  //  1 back (print nothing)
  int register_res = -2;
  while (1) {
    if (this->have_to_logout) {
      cout << "Your account has been deleted" << endl;
      cout << "or your password has been changed in another session" << endl;
      cout << "Press any key to continue :D" << endl;
      Input(false, -1, maxLenPress, true);
      SendMessage("#exited");
      this->have_to_logout = false;
    }
    // print authentication menu
    system("clear");
    gotoxy(1, 1);
    for (int i = 0; i < 33; i++) {
      cout << "-";
    }
    cout << defCol << "\n|" << bgYellowfgBlack
         << "     Authentication Menu       " << defCol << "|\n";
    for (int i = 0; i < 33; i++) {
      cout << "-";
    }
    cout << endl;
    cout << defCol << "|" << colors[1] << "F1.         Register           "
         << defCol << "|\n";
    cout << "|                               |\n";
    cout << defCol << "|" << colors[2] << "F2.          Login             "
         << defCol << "|\n";
    cout << "|                               |\n";
    cout << defCol << "|" << colors[4] << "F4.          Exit              "
         << defCol << "|\n";
    for (int i = 0; i < 33; i++) {
      cout << "-";
    }
    cout << endl;
    // end print authentication menu
    if (is_invalid_press) {
      gotoxy(1, 10);
      cout << "Invalid choice!\n";
      is_invalid_press = false;
    }
    if (register_res != -2) {
      if (register_res == -1) {
        cout << colors[0] << "Register failed!" << defCol;
      } else if (register_res == 0) {
        cout << colors[1] << "Account registered" << defCol;
      }
      cout << endl;
      register_res = -2;
    }
    press = Input(false, -1, maxLenPress, true);
    if (press == "#F1") {
      register_res = Register();
    } else if (press == "#F2") {
      if (Login() == 0) {
        ChatConsole();
      }
    } else if (press == "#exit") {
      SendMessage("#exit");
      close(this->client_socket);
      return 0;
    } else {
      is_invalid_press = true;
    }
  }
}
int Client::Register() {
  // Sending message to server is Register
  char exit_register[MAX_LEN] = "#exit_register";  // NOLINT
  // print register menu
  system("clear");
  gotoxy(1, 1);
  for (int i = 0; i < 33; i++) {
    cout << "-";
  }
  cout << defCol << "\n|" << bgYellowfgBlack
       << "         Register Form         " << defCol << "|\n";
  for (int i = 0; i < 33; i++) {
    cout << "-";
  }
  cout << endl;
  cout << defCol << "|" << colors[1]
       << "Username:                      " << defCol << "|\n";
  cout << "|                               |\n";
  cout << defCol << "|" << colors[2]
       << "Password:                      " << defCol << "|\n";
  cout << "|                               |\n";
  cout << defCol << "|" << colors[4] << "F4. Back                       "
       << defCol << "|\n";
  for (int i = 0; i < 33; i++) {
    cout << "-";
  }
  cout << endl;
  // end print register menu
  string message = "1";  // send to server for server to set stage to register
                         // stage for this client
  SendMessage(message);
  string username, password;
  string check;
  gotoxy(12, 4);
  username = Input(false, 1, maxLenUsername, false);

  while (username.size() == 0 || username == "#F1" || username == "#F2" ||
         username == "#F3") {
    if (username.size() == 0) {
      gotoxy(1, 10);
      cout << "Username can't be empty!" << endl;
      gotoxy(12, 4);
      cout << string(maxLenUsername, ' ');
      gotoxy(12, 4);
    }
    username = Input(false, 1, maxLenUsername, false);
  }

  if (username == "#exit") {
    SendMessage("#exit_register");
    return 1;  // back to authentication menu
  }
  SendMessage(username);
  gotoxy(12, 6);

  password = Input(false, 0, maxLenPassword, false);

  while (password.size() == 0 || password == "#F1" || password == "#F2" ||
         password == "#F3") {
    if (password.size() == 0) {
      gotoxy(1, 10);
      cout << "Password can't be empty!" << endl;
      gotoxy(12, 6);
      cout << string(maxLenPassword, ' ');
      gotoxy(12, 6);
    }
    password = Input(false, 0, maxLenPassword, false);
  }

  if (password == "#exit") {
    SendMessage("#exit_register");
    return 1;  // back to authentication menu
  }
  SendMessage(password);
  check = RecvMessage(this->client_socket).second;
  if (check == "#register_fail") {
    return -1;
  } else if (check == "#register_success") {
    return 0;
  }
}

int Client::ChatConsole() {
  bool is_invalid_choice = false;
  while (1) {
    // print main menu
    gotoxy(1, 1);
    system("clear");
    for (int i = 0; i < 33; i++) {
      cout << "-";
    }
    cout << defCol << "\n|" << bgYellowfgBlack
         << "           Chat menu           " << defCol << "|\n";
    for (int i = 0; i < 33; i++) {
      cout << "-";
    }
    cout << endl;
    cout << defCol << "|" << colors[1] << "F1.  Choose user for chatting  "
         << defCol << "|\n";
    cout << "|                               |\n";
    cout << defCol << "|" << colors[2] << "F2.       Change Password      "
         << defCol << "|\n";
    cout << "|                               |\n";
    cout << defCol << "|" << colors[3] << "F3.       Delete Account       "
         << defCol << "|\n";
    cout << "|                               |\n";
    cout << defCol << "|" << colors[4] << "F4.           Logout           "
         << defCol << "|\n";
    for (int i = 0; i < 33; i++) {
      cout << "-";
    }
    cout << endl;
    // end print main menu
    if (is_invalid_choice) {
      cout << "Invalid choice!";
      is_invalid_choice = false;
    }
    gotoxy(1, 12);
    string navigation = Input(false, -1, maxLenPress, true);
    if (navigation == "#F1") {
      this->exit_flag = false;
      SendMessage("#F1");
      Client::RoomConsole();
      if (this->have_to_logout) return -1;
    } else if (navigation == "#F2") {
      SendMessage("#F2");
      int change_pass_res = Client::ModifyConsole();
      if (this->have_to_logout) return -1;
      if (change_pass_res == 0) {
        return 0;
      }
    } else if (navigation == "#F3") {
      cout << "Delete Account" << endl;
      int delete_account_res = Client::DeleteConfirmConsole();
      if (delete_account_res == 1)
        continue;
      else
        break;
    } else if (navigation == "#exit") {
      SendMessage("#exit_chatcsl");
      break;
    } else {
      is_invalid_choice = true;
    }
  }
  return 0;
}

int Client::ModifyConsole() {
  string password_old, password_new, password_retype;
  string change_res;                // response msg recv from server
  bool is_retype_match = true;      // whether new and retype pass the same
  bool is_retype_old_same = false;  // whether new and old pass the same
  bool is_wrong_password = false;   // whether old password wrong
  string empty_warning = "Password can't be empty!";
  string retype_match_warning = "Retype password isn't match!";
  string retype_old_warning = "New password can't be the same as old password!";
  string warning_clear(retype_old_warning.size(), ' ');
  while (1) {
    system("clear");
    gotoxy(1, 1);
    for (int i = 0; i < 33; i++) {
      cout << "-";
    }
    cout << defCol << "\n|" << bgYellowfgBlack
         << "     Change Password Form      " << defCol << "|\n";
    for (int i = 0; i < 33; i++) {
      cout << "-";
    }
    cout << endl;
    cout << defCol << "|" << colors[1]
         << "Old Password:                  " << defCol << "|\n";
    cout << "|                               |\n";
    cout << defCol << "|" << colors[2]
         << "New Password:                  " << defCol << "|\n";
    cout << "|                               |\n";
    cout << defCol << "|" << colors[3]
         << "Retype Password:               " << defCol << "|\n";
    cout << "|                               |\n";
    cout << defCol << "|" << colors[4] << "F4. Back                       "
         << defCol << "|\n";
    for (int i = 0; i < 33; i++) {
      cout << "-";
    }
    cout << endl;
    if (is_wrong_password) {
      gotoxy(1, 12);
      cout << "Wrong old password" << endl;
      is_wrong_password = false;
    }
    // input old password
    gotoxy(16, 4);
    password_old = Input(false, 0, maxLenPassword, false);
    while (password_old.size() == 0 || password_old == "#F1" ||
           password_old == "#F2" || password_old == "#F3") {
      if (password_old.size() == 0) {
        gotoxy(1, 12);
        cout << empty_warning << endl;
        gotoxy(16, 4);
        cout << string(maxLenPassword, ' ');
        gotoxy(16, 4);
      }
      password_old = Input(false, 0, maxLenPassword, false);
    }
    gotoxy(1, 12);
    cout << warning_clear << endl;
    if (password_old == "#exit") {
      SendMessage("#exit_change");
      return 1;
    }
    do {
      if (!is_retype_match) {
        gotoxy(1, 12);
        cout << warning_clear << endl;
        gotoxy(1, 12);
        cout << retype_match_warning << endl;
        gotoxy(16, 6);
        cout << string(maxLenPassword, ' ');
        gotoxy(19, 8);
        cout << string(maxLenPassword, ' ');
      } else if (is_retype_old_same) {
        gotoxy(1, 12);
        cout << warning_clear << endl;
        gotoxy(1, 12);
        cout << retype_old_warning << endl;
        gotoxy(16, 4);
        cout << string(maxLenPassword, ' ');
        gotoxy(16, 6);
        cout << string(maxLenPassword, ' ');
        gotoxy(19, 8);
        cout << string(maxLenPassword, ' ');
        // input old password in case is_retype_old_same
        gotoxy(16, 4);
        password_old = Input(false, 0, maxLenPassword, false);
        while (password_old.size() == 0 || password_old == "#F1" ||
               password_old == "#F2" || password_old == "#F3") {
          if (password_old.size() == 0) {
            gotoxy(1, 12);
            cout << empty_warning << endl;
            gotoxy(16, 4);
            cout << string(maxLenPassword, ' ');
            gotoxy(16, 4);
          }
          password_old = Input(false, 0, maxLenPassword, false);
        }
        gotoxy(1, 12);
        cout << warning_clear << endl;
        if (password_old == "#exit") {
          SendMessage("#exit_change");
          return 1;
        }
      }
      gotoxy(16, 6);
      password_new = Input(false, 0, maxLenPassword, false);
      while (password_new.size() == 0 || password_new == "#F1" ||
             password_new == "#F2" || password_new == "#F3") {
        if (password_new.size() == 0) {
          gotoxy(1, 12);
          cout << empty_warning << endl;
          gotoxy(16, 6);
          cout << string(maxLenPassword, ' ');
          gotoxy(16, 6);
        }
        password_new = Input(false, 0, maxLenPassword, false);
      }
      if (password_new == "#exit") {
        SendMessage("#exit_change");
        return 1;
      }
      gotoxy(1, 12);
      cout << warning_clear << endl;
      gotoxy(19, 8);

      password_retype = Input(false, 0, maxLenPassword, false);

      while (password_retype.size() == 0 || password_retype == "#F1" ||
             password_retype == "#F2" || password_retype == "#F3") {
        if (password_retype.size() == 0) {
          gotoxy(1, 12);
          cout << empty_warning << endl;
          gotoxy(19, 8);
          cout << string(maxLenPassword, ' ');
          gotoxy(19, 8);
        }
        password_retype = Input(false, 0, maxLenPassword, false);
      }
      if (password_retype == "#exit") {
        SendMessage("#exit_change");
        return 1;
      }
      gotoxy(1, 12);
      cout << warning_clear << endl;
      if (password_new != password_retype) {
        is_retype_match = false;
        continue;
      } else {
        is_retype_match = true;
      }
      if (password_old == password_retype) {
        is_retype_old_same = true;
        continue;
      }
      break;
    } while (1);
    SendMessage(password_old);
    usleep(100);
    SendMessage(password_new);
    change_res = RecvMessage(this->client_socket).second;
    if (change_res == "#exit") {
      this->have_to_logout = true;
      return -1;
    }
    if (change_res == "#wrong_change_info") {
      is_wrong_password = true;
      continue;
    } else {
      if (change_res == "#change_fail") {
        gotoxy(1, 12);
        cout << "Change password failed" << endl;
        Input(false, -1, maxLenPress, true);
        return -1;
      }
      return 0;
    }
  }
}

int Client::RoomConsole() {
  bool is_invalid_choice = false;
  while (1) {
    // print room menu
    gotoxy(1, 1);
    system("clear");
    for (int i = 0; i < 33; i++) {
      cout << "-";
    }
    cout << defCol << "\n|" << bgYellowfgBlack
         << "  Choose room or Create room?  " << defCol << "|\n";
    for (int i = 0; i < 33; i++) {
      cout << "-";
    }
    cout << endl;
    cout << defCol << "|" << colors[1] << "F1.        Choose room         "
         << defCol << "|\n";
    cout << "|                               |\n";
    cout << defCol << "|" << colors[2] << "F2.        Create room         "
         << defCol << "|\n";
    cout << "|                               |\n";
    cout << defCol << "|" << colors[3] << "F4.           Back             "
         << defCol << "|\n";
    cout << "|                               |\n";
    for (int i = 0; i < 33; i++) {
      cout << "-";
    }
    cout << endl;
    // end print room menu
    if (is_invalid_choice) {
      cout << "Invalid choice";
      is_invalid_choice = false;
    }
    gotoxy(1, 12);
    string navigation = Input(false, -1, maxLenPress, true);
    if (navigation == "#F1") {
      SendMessage("#choose_room");
      Client::ChooseRoomConsole();
    } else if (navigation == "#F2") {
      SendMessage("#create_room");
      Client::CreateRoomConsole();
    } else if (navigation == "#exit") {
      SendMessage("#exit_choose_room");
      return 1;
    } else {
      is_invalid_choice = true;
    }
    if (this->have_to_logout) return -1;
  }
}

int Client::DeleteConfirmConsole() {
  // print delete menu
  system("clear");
  for (int i = 0; i < 33; i++) {
    cout << "-";
  }
  cout << defCol << "\n|" << bgYellowfgBlack
       << "        Delete Confirm         " << defCol << "|\n";
  for (int i = 0; i < 33; i++) {
    cout << "-";
  }
  cout << endl;
  cout << defCol << "|" << colors[1] << "F1.           Yes              "
       << defCol << "|\n";
  cout << "|                               |\n";
  cout << defCol << "|" << colors[2] << "F2.           No               "
       << defCol << "|\n";

  cout << "|                               |\n";
  for (int i = 0; i < 33; i++) {
    cout << "-";
  }
  cout << endl;
  // end print delete menu
  string choice;
  while (1) {
    choice = Input(false, -1, maxLenPress, true);
    if (choice == "#F1") {
      SendMessage("#F3");
      string delete_res = RecvMessage(this->client_socket).second;
      if (delete_res == "#exit") {
        this->have_to_logout = true;
        return -1;
      }
      // if (delete_res == "#delete_success") {
      if(delete_res == "#delete_success") {
        cout << "Delete success. Enter to continue :D" << endl;
        Input(false, -1, maxLenPress, true);
        return 0;
      } else if (delete_res == "#delete_fail") {
        cout << "Delete fail. Enter to continue D:" << endl;
        Input(false, -1, maxLenPress, true);
        return -1;
      }
    } else if (choice == "#F2") {
      return 1;
    } else {
      continue;
    }
  }
}

int Client::ChooseRoomConsole() {
  bool is_room_id_valid = true;
  string list_room, room_id_char, old_msg;
  list_room = RecvMessage(this->client_socket).second;
  if (list_room == "#exit") {
    this->have_to_logout = true;
    return -1;
  }
  fflush(stdout);
  system("clear");
  string list_room_str, room_id;
  list_room_str = list_room;
  if (list_room == "#no_room") {
    cout << "You don't have any room!!!" << endl << "Enter to continue :D";
    Input(false, -1, maxLenPress, true);
    return 1;
  } else {
    vector<vector<string>> split_str_room =
        Client::SplitStringRoom(list_room_str);
    while (1) {
      Client::PrintRoomMenu(split_str_room);
      if (!is_room_id_valid) {
        gotoxy(1, 7 + 2 * split_str_room.size());
        cout << colors[4] << "Invalid room id" << defCol;
        gotoxy(1, 6 + 2 * split_str_room.size());
        cout << string(maxLenRoomId, ' ') << string(maxLenRoomId, '\b');
        is_room_id_valid = true;
      }
      cout << "Room id: ";
      room_id = Input(false, 1, maxLenRoomId, false);
      while (room_id == "") {
        room_id = Input(false, 1, maxLenRoomId, false);
      }
      if (room_id == "#exit") {
        SendMessage("#exit_choose_room_id");
        return 1;
      } else {
        if (!isValidRoomChoice(split_str_room, room_id)) {
          is_room_id_valid = false;
          continue;
        } else {
          is_room_id_valid = true;
          break;
        }
      }
    }
    for (int i = 0; i < split_str_room.size() - 1; i++) {
      if (room_id == split_str_room[i][0]) {
        if (split_str_room[i][1].find(seperator3) != string::npos) {
          vector<string> users = Split(split_str_room[i][1], seperator3);
          if (users[0] == string(this->name_str)) {
            this->room_name_id = users[1];
          } else {
            this->room_name_id = users[0];
          }
          break;
        }
        this->room_name_id = split_str_room[i][1];
        break;
      }
    }
    SendMessage(room_id);
    fflush(stdout);
    old_msg = RecvMessage(this->client_socket).second;
    if (old_msg == "#exit") {
      this->have_to_logout = true;
      return -1;
    }
    fflush(stdout);
    system("clear");
    gotoxy(1, 6);
    cout << old_msg;
    return CreateThread();
  }
}

int Client::PrintRoomMenu(vector<vector<string>> room) {
  system("clear");
  for (int i = 0; i < 33; i++) {
    cout << "-";
  }
  cout << defCol << "\n|" << bgYellowfgBlack
       << "          List Room            " << defCol << "|\n";
  for (int i = 0; i < 33; i++) {
    cout << "-";
  }
  cout << defCol << "\n|"
       << "ID" << ' ' << "|"
       << "Room name" << string(18, ' ') << defCol << "|\n";
  for (int i = 0; i < 33; i++) {
    cout << "-";
  }
  string room_name;
  vector<string> users;
  for (int i = 0; i < room.size() - 1; i++) {
    room_name = room[i][1];
    if (room_name.find(seperator3) != string::npos) {
      users = Split(room_name, seperator3);

      if (users[0] == string(this->name_str)) {
        room_name = users[1];
      } else {
        room_name = users[0];
      }
    }
    cout << defCol << "\n|" << colors[(i + 1) % 5] << room[i][0]
         << string(3 - room[i][0].size(), ' ') << "|" << room_name
         << string(27 - room_name.size(), ' ') << defCol << "|\n";
    cout << "|                               |";
  }
  cout << endl;
  for (int i = 0; i < 33; i++) {
    cout << "-";
  }
  cout << endl;
  cout << "Enter Room ID to choose Room" << endl;
  return 0;
}

int Client::CreateRoomConsole() {
  string list_user = RecvMessage(this->client_socket).second;
  if (list_user == "#exit") {
    this->have_to_logout = true;
    return -1;
  }
  // string list_user_str = list_user;
  fflush(stdout);
  system("clear");
  if (list_user == "#no_user") {
    cout << "You don't have any friend!!!";
    cout << endl << "Enter to continue :D";
    Input(false, -1, maxLenPress, true);
    return 1;
  }
  vector<string> user_splitted = Split(list_user, seperator1);
  Client::PrintUserMenu(user_splitted);
}

int Client::PrintUserMenu(vector<string> users) {
  system("clear");
  for (int i = 0; i < 33; i++) {
    cout << "-";
  }
  cout << defCol << "\n|" << bgYellowfgBlack
       << "          List User            " << defCol << "|\n";
  for (int i = 0; i < 33; i++) {
    cout << "-";
  }
  cout << defCol << "\n|"
       << "No." << ' ' << "|"
       << "Username" << string(18, ' ') << defCol << "|\n";
  for (int i = 0; i < 33; i++) {
    cout << "-";
  }
  for (int i = 0; i < users.size() - 1; i++) {
    cout << defCol << "\n|" << colors[(i + 1) % 5] << i + 1
         << string(3 - to_string(i + 1).size(), ' ') << '|' << users[i]
         << string(27 - users[i].size(), ' ') << defCol << "|\n";
    cout << "|                               |";
  }
  cout << endl;
  for (int i = 0; i < 33; i++) {
    cout << "-";
  }
  cout << endl;
  cout << endl << "Enter username to choose user: " << endl;
  int members_str_len = 0;
  vector<string> members;
  string warning_message = "";
  char inputing[MAX_LEN];
  string input;
  string weird_char_warning = "Room name can't contain weird charaters!";
  int max_warning_len = weird_char_warning.size();
  int width, height;
  int warning_position = 5 + 2 * users.size();
  GetScreenSize(width, height);
  if (warning_position >= height - 1) warning_position = height - 2;
  while (1) {
    gotoxy(1, warning_position);
    cout << string(max_warning_len, ' ');
    gotoxy(1, warning_position);
    if (warning_message.size() != 0) {
      cout << colors[0] << warning_message << defCol;
      warning_message = "";
    }
    int next_in_pos_x = (members_str_len % width) + 1;
    int next_in_pos_y = (members_str_len / width) + 7 + 2 * users.size();
    gotoxy(next_in_pos_x, next_in_pos_y);
    memset(inputing, 0, MAX_LEN);
    input = Input(false, 1, maxLenUsername, false, (char(*)[MAX_LEN])inputing);
    if (input == "") {
      warning_message = "Username can't be empty!";
      continue;
    }
    if (input == "#exit") {
      SendMessage("#exit_create_room_id");
      return 1;
    }
    if (input == "#F1") {
      if (members.size() == 0) {
        warning_message = "No member chosen!";
        continue;
      }
      string members_str = "";
      for (int i = 0; i < members.size() - 1; ++i) {
        members_str += members[i] + seperator1;
      }
      members_str += members[members.size() - 1];
      if (members.size() > 1) {
        cout << endl << "Enter room name: ";
        input = Input(false, 1, maxLenUsername, false);
        this->room_name_id = input;
        if (input == "#exit") {
          SendMessage("#exit_create_room_id");
          return 1;
        }
        if (input == "") {
          warning_message = "Room name can't be empty!";
          continue;
        }
        if (input.find('~') != string::npos) {
          warning_message = weird_char_warning;
          continue;
        }
        members_str += seperator2 + input;
      } else {
        this->room_name_id = members[0];
      }
      SendMessage(members_str);
      system("clear");
      fflush(stdout);
      string old_msg = RecvMessage(this->client_socket).second;
      if (old_msg == "#exit") {
        this->have_to_logout = true;
        return -1;
      }
      fflush(stdout);
      system("clear");
      gotoxy(1, 6);
      cout << old_msg;
      return CreateThread();
    }
    if (input == "#F2" || input == "#F3") {
      int inputing_len = strlen(inputing);
      if (members.size() == 0 && inputing_len == 0) {
        warning_message = "No member selected!";
        continue;
      }
      if (inputing_len > 0) {
        cout << string(inputing_len, '\b') << string(inputing_len, ' ')
             << string(inputing_len, '\b');
        continue;
      }
      int last_username_len_plus_comma = members[members.size() - 1].size() + 1;
      cout << string(last_username_len_plus_comma, '\b')
           << string(last_username_len_plus_comma, ' ')
           << string(last_username_len_plus_comma, '\b');
      members_str_len -= last_username_len_plus_comma;
      members.pop_back();
      continue;
    }
    bool is_user_choice_valid = true;
    for (int i = 0; i < members.size(); ++i) {
      if (input == members[i]) {
        is_user_choice_valid = false;
        break;
      }
    }
    bool is_user_exist = false;
    for (int i = 0; i < users.size(); ++i) {
      if (input == users[i]) {
        is_user_exist = true;
        break;
      }
    }
    if (!is_user_exist || !is_user_choice_valid) {
      if (!is_user_exist) warning_message = "Username not exist!";
      if (!is_user_choice_valid) warning_message = "Username already chosen!";
      cout << string(input.size(), '\b') << string(input.size(), ' ')
           << string(input.size(), '\b');
      continue;
    }
    cout << ",";
    members.push_back(input);
    members_str_len += (input.size() + 1);
  }

  return 0;
}

vector<string> Client::Split(string str, char seperator) {
  vector<string> splitted;
  int i = 0;
  int startIndex = 0, endIndex = 0;
  while (i <= str.size()) {
    if (str[i] == seperator || i == str.size()) {
      endIndex = i;
      string subStr = "";
      subStr.append(str, startIndex, endIndex - startIndex);
      splitted.push_back(subStr);
      startIndex = endIndex + 1;
    }
    i++;
  }
  return splitted;
}

vector<vector<string>> Client::SplitStringRoom(string str) {
  vector<string> room1 = Split(str, seperator1);
  vector<vector<string>> room2;
  for (int i = 0; i < room1.size(); ++i) {
    room2.push_back(Split(room1[i], seperator2));
  }
  return room2;
}

bool Client::isValidRoomChoice(const vector<vector<string>> &split_str_room,
                               const string &room_id) {
  for (int i = 0; i < split_str_room.size(); ++i) {
    if (split_str_room[i][0] == room_id) {
      return true;
    }
  }
  return false;
}
int Client::SendMessage(string message) {
  return send(this->client_socket, message.c_str(), message.size() + 1, 0);
}
pair<int, string> Client::RecvMessage(int client_socket) {
  char str[MAX_LEN];
  memset(str, 0, sizeof(str));
  int byte = recv(client_socket, str, sizeof(str), 0);
  string message = string(str);
  return make_pair(byte, message);
}
