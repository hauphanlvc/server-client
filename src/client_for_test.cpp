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
  this->recon_dot_cnt = 0;
  this->count = 0;
  this->is_account_deleted = false;
  this->is_login_failed = false;
  this->room_name = "";
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

int Client::ConnectServer() {
  int sock = connect(this->client_socket, (struct sockaddr *)&this->server_addr,
                     sizeof(struct sockaddr_in));
  while (sock == -1) {
    sock = connect(this->client_socket, (struct sockaddr *)&this->server_addr,
                     sizeof(struct sockaddr_in));
    this->count++;
    if (this->count == 10) {
      cout << "\nTimeout\n";
      StopConnection();
      return -1;
    }
    string recon_msg = "Connection Error. Reconnecting";
    this->recon_dot_cnt = (this->recon_dot_cnt + 1) % 5;
    string dot_str(this->recon_dot_cnt, '.');
    string space_str(5 - this->recon_dot_cnt, ' ');
    string combine_str = dot_str + space_str;
    cout << recon_msg << combine_str;
    fflush(stdout);
    int erase_len = static_cast<int>(recon_msg.length()) +
                    static_cast<int>(combine_str.length());
    sleep(1);
    EraseText(erase_len);
  }
  return sock;
}

int Client::PrintChatKeyControl() {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  int height = w.ws_row;
  int width = w.ws_col;
  const string F4_KEY_CONTROL_STR =
      foregroundBlack + backgroundYellow + "F4: Back" + defCol;
  const int F4_KEY_CONTROL_STR_HAFL_LEN =
      (width - F4_KEY_CONTROL_STR.size()) / 2;

  gotoxy(1, 2);
  cout << string(width, ' ');

  gotoxy(1, 3);
  cout << string(F4_KEY_CONTROL_STR_HAFL_LEN, ' ') << F4_KEY_CONTROL_STR
       << string(width - F4_KEY_CONTROL_STR_HAFL_LEN, ' ');

  gotoxy(1, 4);
  cout << string(width, ' ');

  gotoxy(0, height - 1);
}

// Send message to everyone
int Client::SendMsg() {
  while (1) {
    if (this->exit_flag) return 0;
    PrintChatKeyControl();
    cout << colors[1] << "\n\nYou: " << defCol;
    fflush(stdin);
    memset(this->msg_input, 0, MAX_LEN);
    Input(true, false, MAX_LEN - 1, false, &this->msg_input);
    if (strlen(this->msg_input) > 0) {
      if (strcmp(this->msg_input, "#exit") == 0) {
        char exit_chat[MAX_LEN] = "#exit_chat";
        send(this->client_socket, exit_chat, sizeof(exit_chat), 0);
        this->exit_flag = true;
        this->send_thread.detach();
        this->recv_thread.detach();
        return 0;
      }
      send(this->client_socket, this->msg_input, sizeof(this->msg_input), 0);
    } else {
      cout << string(5, '\b') << string(5, ' ') << string(5, '\b');
      cout << "\nPlease send non-empty message!\n";
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
    char str[MAX_LEN];
    int color_code;

    int recv_bytes =
        recv(this->client_socket, this->name_char, sizeof(this->name_char), 0);
    if (recv_bytes == 0) continue;
    if (recv_bytes < 0) {
      StopConnection();
      exit(1);
    }
    recv(this->client_socket, &color_code, sizeof(color_code), 0);
    recv(this->client_socket, str, sizeof(str), 0);
    if (strcmp(str, "#exit_chat") == 0) return 0;
    EraseText(6);
    if (strcmp(this->name_char, "#NULL") != 0) {
      int len = strlen("You: ") + strlen(this->msg_input);
      string backspace_str = string(len, '\b');
      string space_str = string(len, ' ');
      cout << backspace_str << space_str << backspace_str;
      cout << GetColor(color_code) << this->name_char << " : " << defCol << str
           << endl;
    } else {
      cout << endl << endl << GetColor(color_code) << str << endl;
    }
    cout << colors[1] << "\nYou: " << defCol;
    cout << this->msg_input;
    fflush(stdout);
  }
  // cout << "Stop RecvMSg" << endl;
}

int Client::CreateThread() {
  thread t1(&Client::SendMsg, this);
  thread t2(&Client::RecvMsg, this);
  this->send_thread = move(t1);
  this->recv_thread = move(t2);
  if (this->send_thread.joinable()) this->send_thread.join();
  if (this->recv_thread.joinable()) this->recv_thread.join();
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
  char str[MAX_LEN] = "#exit";
  send(this->client_socket, str, sizeof(str), 0);
  this->exit_flag = true;
  this->send_thread.detach();
  this->recv_thread.detach();
  close(this->client_socket);
}

int Client::Login() {
  char exit_login[MAX_LEN] = "#exit_login";
  while (1) {
    // system("clear");
    if (this->is_login_failed) {
      CreateSocket();
      while (ConnectServer() == -1) {
        CreateSocket();
      }
      gotoxy(1, 10);
      cout << "Wrong username or password or account does not exists";
      is_login_failed = false;
    }
    gotoxy(1, 1);
    for (int i = 0; i < 33; i++) {
      cout << "-";
    }
    cout << defCol << "\n|" << bgRedfgWhite << "         Login Form            "
         << defCol << "|\n";
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

    string message = "2";
    char temp[MAX_LEN];
    strcpy(temp, message.c_str());  // NOLINT
    send(this->client_socket, temp, sizeof(temp), 0);

    string username, password;
    char check[MAX_LEN];
    gotoxy(12, 4);
    username = Input(false, false, maxLenUsername, false);
    while (username.size() == 0) {
      gotoxy(1, 10);
      cout << "Username can't be empty!" << endl;
      gotoxy(12, 4);
      username = Input(false, false, maxLenUsername, false);
    }
    strcpy(this->name_str, username.c_str());  // NOLINT
    if (username == "#exit") {
      send(this->client_socket, exit_login, sizeof(exit_login), 0);
      return 1;
    }
    send(this->client_socket, username.c_str(), sizeof(username), 0);
    gotoxy(12, 6);
    password = Input(false, true, maxLenPassword, false);
    while (password.size() == 0) {
      gotoxy(1, 10);
      cout << "Password can't be empty!" << endl;
      gotoxy(12, 6);
      password = Input(false, true, maxLenPassword, false);
    }
    strcpy(this->password_str, password.c_str());  // NOLINT
    if (password == "#exit") {
      send(this->client_socket, exit_login, sizeof(exit_login), 0);
      return 1;
    }
    send(this->client_socket, password.c_str(), sizeof(password), 0);
    recv(this->client_socket, check, sizeof(check), 0);
    // system("clear");
    if (strcmp(check, "#login_fail") == 0) {
      this->is_login_failed = true;
    } else if (strcmp(check, "#login_success") == 0) {
      this->is_login_failed = false;
      return ChatConsole();
    }
  }
}
int Client::Console() {
  string press;
  bool is_invalid_press = false;
  int register_res = -2;
  while (1) {
    // system("clear");
    gotoxy(1, 1);
    for (int i = 0; i < 33; i++) {
      cout << "-";
    }
    cout << defCol << "\n|" << bgRedfgWhite << "     Authentication Menu       "
         << defCol << "|\n";
    for (int i = 0; i < 33; i++) {
      cout << "-";
    }
    cout << endl;
    cout << defCol << "|" << colors[1] << "1.          Register           "
         << defCol << "|\n";
    cout << "|                               |\n";
    cout << defCol << "|" << colors[2] << "2.           Login             "
         << defCol << "|\n";
    cout << "|                               |\n";
    cout << defCol << "|" << colors[4] << "F4.          Exit              "
         << defCol << "|\n";
    for (int i = 0; i < 33; i++) {
      cout << "-";
    }
    cout << endl;
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
    press = Input(false, false, maxLenPress, true);
    if (press == "1") {
      register_res = Register();
    } else if (press == "2") {
      Login();
    } else if (press == "#exit") {
      char str[MAX_LEN] = "#exit";
      send(this->client_socket, str, sizeof(str), 0);
      close(this->client_socket);
      exit(0);
    } else {
      is_invalid_press = true;
    }
  }
}
int Client::Register() {
  // Sending message to server is Register
  char exit_register[MAX_LEN] = "#exit_register";
  // system("clear");
  gotoxy(1, 1);
  for (int i = 0; i < 33; i++) {
    cout << "-";
  }
  cout << defCol << "\n|" << bgRedfgWhite << "         Register Form         "
       << defCol << "|\n";
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
  string message = "1";
  char temp[MAX_LEN];
  strcpy(temp, message.c_str());  // NOLINT
  send(this->client_socket, temp, sizeof(temp), 0);
  string username, password;
  char check[MAX_LEN];
  gotoxy(12, 4);
  username = Input(false, false, maxLenUsername, false);
  while (username.size() == 0) {
    gotoxy(1, 10);
    cout << "Username can't be empty!" << endl;
    gotoxy(12, 4);
    username = Input(false, false, maxLenUsername, false);
  }
  strcpy(this->name_str, username.c_str());  // NOLINT

  if (username == "#exit") {
    send(this->client_socket, exit_register, sizeof(exit_register), 0);
    return 1;
  }
  send(this->client_socket, username.c_str(), sizeof(username), 0);
  gotoxy(12, 6);
  password = Input(false, true, maxLenPassword, false);
  while (password.size() == 0) {
    gotoxy(1, 10);
    cout << "Password can't be empty!" << endl;
    gotoxy(12, 6);
    password = Input(false, true, maxLenPassword, false);
  }
  strcpy(this->password_str, password.c_str());  // NOLINT
  if (password == "#exit") {
    send(this->client_socket, exit_register, sizeof(exit_register), 0);
    return 1;
  }
  send(this->client_socket, password.c_str(), sizeof(password), 0);

  recv(this->client_socket, check, sizeof(check), 0);
  if (strcmp(check, "#register_fail") == 0) {
    return -1;
  } else if (strcmp(check, "#register_success") == 0) {
    return 0;
  }
}

int Client::ChatConsole() {
  while (1) {
    // system("clear");
    for (int i = 0; i < 33; i++) {
      cout << "-";
    }
    cout << defCol << "\n|" << bgRedfgWhite << "           Chat menu           "
         << defCol << "|\n";
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
    cout << defCol << "|" << colors[4] << "F4.            Back            "
         << defCol << "|\n";
    for (int i = 0; i < 33; i++) {
      cout << "-";
    }
    cout << endl;
    gotoxy(1, 12);
    // cout << "Login success";
    string navigation = Input(false, false, maxLenPress, true);
    char old_msg[MAX_LEN];
    if (navigation == "#F1") {
      this->exit_flag = false;
      cout << "Start Chatting" << endl;
      int color_code;
      char str[MAX_LEN] = "#F1";
      send(this->client_socket, str, sizeof(str), 0);
      fflush(stdout);
      recv(this->client_socket, old_msg, sizeof(old_msg), 0);
      fflush(stdout);
      cout << old_msg;
      CreateThread();

    } else if (navigation == "#F2") {
      char str[MAX_LEN] = "#F2";
      send(this->client_socket, str, sizeof(str), 0);
      int change_pass_res = Client::ModifyConsole();
      if (change_pass_res == 0) {
        return change_pass_res;
      } else if (change_pass_res == 1) {
        char exit_change[MAX_LEN] = "#exit_change";
        send(this->client_socket, exit_change, sizeof(exit_change), 0);
        continue;
      }

    } else if (navigation == "#F3") {
      cout << "Delete Account" << endl;
      Client::DeleteConfirmConsole();
      if (!this->is_account_deleted)
        continue;
      else
        break;
    } else if (navigation == "#exit") {
      char exit_chatcsl[MAX_LEN] = "#exit_chatcsl";
      send(this->client_socket, exit_chatcsl, sizeof(exit_chatcsl), 0);
      break;
    }
  }
}

int Client::ModifyConsole() {
  string password_old, password_new, password_retype;
  char *change_res[MAX_LEN];
  bool is_retype_match = true;
  bool is_retype_old_same = false;
  bool is_wrong_password = false;
  string empty_warning = "Password can't be empty!";
  string retype_match_warning = "Retype password isn't match!";
  string retype_old_warning = "Retype can't be the same as old password!";
  string warning_clear(retype_old_warning.size(), ' ');
  while (1) {
    // system("clear");
    gotoxy(1, 1);
    for (int i = 0; i < 33; i++) {
      cout << "-";
    }
    cout << defCol << "\n|" << bgRedfgWhite << "     Change Password Form      "
         << defCol << "|\n";
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
    password_old = Input(false, true, maxLenPassword, false);
    while (password_old.size() == 0) {
      gotoxy(1, 12);
      cout << empty_warning << endl;
      gotoxy(16, 4);
      password_old = Input(false, true, maxLenPassword, false);
    }
    gotoxy(1, 12);
    cout << warning_clear << endl;
    if (password_old == "#exit") {
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
        password_old = Input(false, true, maxLenPassword, false);
        while (password_old.size() == 0) {
          gotoxy(1, 12);
          cout << empty_warning << endl;
          gotoxy(16, 4);
          password_old = Input(false, true, maxLenPassword, false);
        }
        gotoxy(1, 12);
        cout << warning_clear << endl;
        if (password_old == "#exit") {
          return 1;
        }
      }
      gotoxy(16, 6);
      password_new = Input(false, true, maxLenPassword, false);
      while (password_new.size() == 0) {
        gotoxy(1, 12);
        cout << empty_warning << endl;
        gotoxy(16, 6);
        password_new = Input(false, true, maxLenPassword, false);
      }
      if (password_new == "#exit") {
        return 1;
      }
      gotoxy(1, 12);
      cout << warning_clear << endl;
      gotoxy(19, 8);
      password_retype = Input(false, true, maxLenPassword, false);
      while (password_retype.size() == 0) {
        gotoxy(1, 12);
        cout << empty_warning << endl;
        gotoxy(19, 8);
        password_retype = Input(false, true, maxLenPassword, false);
      }
      if (password_retype == "#exit") {
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

    send(client_socket, password_old.c_str(), MAX_LEN, 0);
    send(client_socket, password_new.c_str(), MAX_LEN, 0);
    recv(client_socket, change_res, MAX_LEN, 0);
    string change_res_str(reinterpret_cast<char *>(change_res));
    if (change_res_str == "-2") {
      is_wrong_password = true;
      continue;
    } else {
      if (change_res_str == "-1") {
        gotoxy(1, 12);
        cout << "Change password failed" << endl;
        Getch();
      }
      char exit[MAX_LEN] = "#exit";
      send(this->client_socket, exit, sizeof(exit), 0);
      close(this->client_socket);
      return 0;
    }
  }
}

int Client::DeleteConfirmConsole() {
  int startx = 0;
  int starty = 0;
  int WIDTH = 30;
  int HEIGHT = 10;
  char *choices[] = {
      "Yes",
      "No",
  };
  int n_choices = sizeof(choices) / sizeof(char *);
  WINDOW *menu_win;
  int highlight = 1;
  int choice = 0;
  int c;

  initscr();
  clear();
  noecho();
  cbreak(); /* Line buffering disabled. pass on everything */
  startx = (80 - WIDTH) / 2;
  starty = (24 - HEIGHT) / 2;

  menu_win = newwin(HEIGHT, WIDTH, starty, startx);
  keypad(menu_win, TRUE);
  mvprintw(0, 0,
  "Use arrow keys to go up and down, Press enter to select a choice");

  start_color();

  init_pair(1, COLOR_WHITE, COLOR_RED);

  attron(COLOR_PAIR(1));
  mvprintw(6, 20, "Are you sure you want to delete your account?");
  attroff(COLOR_PAIR(1));

  refresh();
  int x, y, i;

  x = 2;
  y = 2;
  box(menu_win, 0, 0);
  for (i = 0; i < n_choices; ++i) {
    if (highlight == i + 1) {
      wattron(menu_win, A_REVERSE);
      mvwprintw(menu_win, y, x, "%s", choices[i]);
      wattroff(menu_win, A_REVERSE);
    } else {
      mvwprintw(menu_win, y, x, "%s", choices[i]);
    }
    ++y;
  }
  wrefresh(menu_win);
  while (1) {
    c = wgetch(menu_win);
    switch (c) {
      case KEY_UP:
        if (highlight == 1)
          highlight = n_choices;
        else
          --highlight;
        break;
      case KEY_DOWN:
        if (highlight == n_choices)
          highlight = 1;
        else
          ++highlight;
        break;
      case 10:
        choice = highlight;
        break;
      default:
        mvprintw(
            24, 0,
            "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c,
            c);
        refresh();
        break;
    }
    int x, y, i;

    x = 2;
    y = 2;
    box(menu_win, 0, 0);
    for (i = 0; i < n_choices; ++i) {
      if (highlight == i + 1) {
        wattron(menu_win, A_REVERSE);
        mvwprintw(menu_win, y, x, "%s", choices[i]);
        wattroff(menu_win, A_REVERSE);
      } else {
        mvwprintw(menu_win, y, x, "%s", choices[i]);
      }
      ++y;
    }
    wrefresh(menu_win);
    if (choice != 0) /* User did a choice come out of the infinite loop */
      break;
  }
  if (choice == 1) {
    char f3[MAX_LEN] = "#F3";
    send(this->client_socket, f3, sizeof(f3), 0);
    cout << "Delete Account" << endl;
    char exit[MAX_LEN] = "#exit";
    send(this->client_socket, exit, sizeof(exit), 0);
    close(this->client_socket);
    this->is_account_deleted = true;
    clrtoeol();
    refresh();
    endwin();
  } else {
    this->is_account_deleted = false;
    clrtoeol();
    refresh();
    endwin();
  }
}
