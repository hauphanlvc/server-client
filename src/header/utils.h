// Copyright 2022

#ifndef SRC_HEADER_UTILS_H_
#define SRC_HEADER_UTILS_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#endif  // SRC_HEADER_UTILS_H_
using std::cout;
using std::find;
using std::string;
using std::vector;
#define MAX_LEN 20000

const int maxChatContent = 1000;

bool CheckCodes(const vector<char> &codes) {
  // four or five code-combines special key common prefix codes
  if (codes[0] == 27 && codes[1] == 91) return true;
  // first case five code-combines special key sub codes
  if (codes[0] == 91 && codes[1] == 49) return true;
  // second case five code-combines special key sub codes
  if (codes[0] == 91 && codes[1] == 50) return true;
  return false;
}

int Getch() {
  int ch;
  struct termios t_old, t_new;
  tcgetattr(STDIN_FILENO, &t_old);
  t_new = t_old;
  t_new.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &t_new);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &t_old);
  return ch;
}

string Input(bool is_space_allowed, int print_flag, int max_len,
             bool return_at_max_len, char (*input)[MAX_LEN] = NULL) {
  const char BACKSPACE1 = 127;
  const char BACKSPACE2 = 8;
  const char RETURN = 10;
  const char SPACE = 32;
  const char ZERO = 48;
  const char NINE = 57;
  const char LAST_OF_F1 = 80;
  const char LAST_OF_F2 = 81;
  const char LAST_OF_F3 = 82;
  const char LAST_OF_F4 = 83;
  // const char LAST_OF_LEFT = 68;
  string str;
  unsigned char ch = 0;
  vector<char> special_codes({9,  27, 32, 35, 48, 49, 50, 51, 52, 53,
                              54, 55, 56, 57, 65, 66, 67, 68, 70, 72,
                              79, 80, 81, 82, 83, 91, 96, 126});
  vector<char> codes_queue({0, 0, 0});
  int input_init_len = 0;
  if (input) input_init_len = strlen(*input);
  while ((ch = Getch()) != RETURN) {
    if (input && input_init_len + str.size() > maxChatContent - 1) continue;
    // cout << "ch:" << int(ch);
    codes_queue.erase(codes_queue.begin());
    codes_queue.push_back(ch);
    if (find(special_codes.begin(), special_codes.end(), ch) !=
        special_codes.end()) {
      if (ch == LAST_OF_F4) {
        if (input) strcpy((*input) + input_init_len, "#exit");  // NOLINT
        return "#exit";
      }
      if (ch == LAST_OF_F1) {
        if (input) strcpy((*input) + input_init_len, str.c_str());  // NOLINT
        return "#F1";
      }
      if (ch == LAST_OF_F2) {
        if (input) strcpy((*input) + input_init_len, str.c_str());  // NOLINT
        return "#F2";
      }
      if (ch == LAST_OF_F3) {
        if (input) strcpy((*input) + input_init_len, str.c_str());  // NOLINT
        return "#F3";
      }
      if (ch >= ZERO && ch <= NINE) {
        if (CheckCodes(codes_queue)) continue;
      } else {
        if (!(ch == SPACE && is_space_allowed)) continue;
      }
    }
    if (ch == BACKSPACE1 || ch == BACKSPACE2) {
      if (str.length() != 0) {
        cout << "\b \b";
        str.resize(str.length() - 1);
        if (input) strcpy((*input) + input_init_len, str.c_str());  // NOLINT
      } else if (input && strlen(*input) != 0) {
        cout << "\b \b";
        (*input)[strlen(*input) - 1] = '\0';
      }
    } else {
      if (return_at_max_len) {
        str += ch;
        if (print_flag == 1)
          cout << ch;
        else if (print_flag == 0)
          cout << '*';
        if (str.size() == max_len) return str;
      } else {
        if (str.size() == max_len) continue;
      }
      str += ch;
      if (input) strcpy((*input) + input_init_len, str.c_str());  // NOLINT
      if (print_flag == 1)
        cout << ch;
      else if (print_flag == 0)
        cout << '*';
    }
  }
  return str;
}

void gotoxy(int x, int y) { printf("%c[%d;%df", 0x1B, y, x); }

int GetScreenSize(int &width, int &height) {  // NOLINT
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  height = w.ws_row;
  width = w.ws_col;
}
