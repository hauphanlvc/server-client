#include "client.h"

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
    sleep(1);
  }
  return 0;
}



string Client::GetColor(int code) { return colors[code % NUM_COLORS]; }

int Client::StopConnection() {
//   SendMessage("#exit");
  this->exit_flag = true;
//   this->send_thread.detach();
//   this->recv_thread.detach();
  close(this->client_socket);
}
int Client::SendMessage(string message) {
  return send(this->client_socket, message.c_str(), message.size() + 1, 0);
}
pair<int, string> Client::RecvMessage() {
  char str[MAX_LEN];
  memset(str, 0, sizeof(str));
  int byte = recv(this->client_socket, str, sizeof(str), 0);
  string message = string(str);
  return make_pair(byte, message);
}
int Client::CloseConnection() {
    return close(this->client_socket);
}
int Client::setname_str(string username) {
    this->name_str = username;
}
string Client::get_name_str() {
    return this->name_str;
}
vector<string> Client::SplitString(string str, string del) {
    int start, end = -1*del.size();
    vector<string> result;
    do {
        start = end + del.size();
        end = str.find(del,start);
        // cout << str.substr(start,end - start) << endl;
        result.push_back(str.substr(start,end - start));
    } while (end != -1);
    return result;


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
