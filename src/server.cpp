// Copyright 2022

#include "header/server.h" //NOLINT
Server::Server()
{
  int port = atoi(getenv("PORT"));

  if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    perror("socket: ");
    exit(-1);
  }
  int enable = 1;
  if (setsockopt(server_socket, SOL_SOCKET,
                 SO_REUSEADDR, // NOLINT
                 &enable, sizeof(int)) < 0)
    cerr << "setsockopt(SO_REUSEADDR) failed" << endl;

  if (setsockopt(server_socket, SOL_SOCKET,
                 SO_REUSEPORT, // NOLINT
                 &enable, sizeof(int)) < 0)
    cerr << "setsockopt(SO_REUSEPORT) failed" << endl;

  if (ioctl(server_socket, FIONBIO, reinterpret_cast<char *>(&enable)))
  {
    perror("ioctl() failed");
    exit(-1);
  }
  struct sockaddr_in server;
  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  bzero(&server.sin_zero, 0);
  if ((bind(server_socket, (struct sockaddr *)&server,
            sizeof(struct sockaddr_in))) == -1)
  {
    perror("bind error: ");
    exit(-1);
  }

  srand(time(NULL));
}

int Server::ConnectToClients()
{
  if ((listen(server_socket, 8)) == -1)
  {
    perror("listen error: ");
    close(server_socket);
    return -1;
  }
  cout << "server listening" << endl;
  struct sockaddr_in client;
  int client_socket;
  int nfds = 1;
  unsigned int len = sizeof(sockaddr_in);
  memset(clients_fds, 0, sizeof(clients_fds));
  int current_size = 0;
  clients_fds[0].fd = server_socket;
  clients_fds[0].events = POLLIN;
  for (int i = 1; i < MAX_CLIENTS; i++)
  {
    clients_fds[i].fd = -1;
  }

  int rc;
  do
  {
    rc = poll(clients_fds, nfds, -1);
    if (rc < 0)
    {
      perror("poll() failed");
      break;
    }
    if (rc == 0)
    {
      cout << "poll() timed out.";
      break;
    }
    current_size = nfds;
    for (int i = 0; i < current_size; i++)
    {
      // ref code to handle client event
      if (clients_fds[i].revents == 0)
      {
        continue;
      }
      if (clients_fds[i].revents != POLLIN)
      {
        cout << "error! revents = " << clients_fds[i].revents << endl;
        EndConnection(clients_fds[i].fd);
        clients_fds[i].fd = -1;

        close(client_socket);
        continue;
      }
      // end ref code to handle client event
      if (clients_fds[i].fd == server_socket)
      {
        if ((client_socket = accept(server_socket, (struct sockaddr *)&client,
                                    &len)) == -1)
        {
          perror("accept error: ");
          continue;
        }
        cout << "client socket: " << client_socket << endl;
        clients_fds[nfds].fd = client_socket;
        clients_fds[nfds].events = POLLIN;
        login_status.insert({client_socket, false});
        username_of_client_socket.insert({client_socket, ""});
        room_id_of_client_socket.insert({client_socket, -1});
        // username,password,socket,success,stage,menu_id,chat_status,old_password,new_password,room_id,color_id,need_logout

        nfds++;
      }
      else
      {
        pair<int, string> result = RecvMessage(clients_fds[i].fd);
        int byte = result.first;
        string str = result.second;

        if (str.size() == 0)
        {
          continue;
        }

        cout << "++++++++++++++++++++++++++++++\nstr: " << str << endl;
        cout << "str len: " << str.size() << endl;
        client_socket = clients_fds[i].fd;
        if (byte <= 0)
        {
          clients_fds[i].fd = -1;
          EndConnection(client_socket);
          close(client_socket);
          continue;
        }
        auto list_messages = SplitString(str, hash);
        cout << list_messages.size() << endl;
        string option = list_messages[0];
       
        
        if (option != "RECONNECTION")
        {
          cout << "User send: " << username_of_client_socket[client_socket] << endl;
          cout << "option: " << option << endl;
         
          if (option == "#CLOSE") {
          cout << " CLOSE\n" << endl;
          clients_fds[i].fd = -1;
          EndConnection(client_socket);
          close(client_socket);
        } else if (option == "LOGIN")
          {
            cout << "START LOGIN\n";
            // room_id_of_client_socket[client_socket] = -1;
            string user_name = list_messages[1], password = list_messages[2];
            cout << user_name << ": " << password << endl;

            Login(client_socket, user_name, password);
          }
          else if (option == "REGISTER")
          {
            
            cout << "START REGISTER\n";
            string user_name = list_messages[1], password = list_messages[2];
            cout << user_name << ": " << password << endl;
            Register(client_socket, user_name, password);
          }
          else if (option == "LOGOUT")
          {
            
            cout << "START LOGOUT\n";
            if (login_status[client_socket])
            {
              SendMessage(client_socket, "LOGOUT");
              login_status[client_socket] = false;
              username_of_client_socket[client_socket] = "";
            }
          }
          else if (option == "CHANGE_PASSWORD")
          {
            
            cout << "Start Change PassWord\n";
            if (login_status.find(client_socket)->second)
            {
              string old_password = list_messages[1], new_password = list_messages[2];
              cout << "old password: " << old_password << " , new password: " << new_password << endl;

              int status_change_password_int =
                  ChangePassword(username_of_client_socket[client_socket], old_password, new_password);
              if (status_change_password_int == 0)
              {
                cout << "CHANGE PASSWORD SUCCESS" << endl;
                SendMessage(client_socket, "#change_success");

                SendExitToClientsByUsername(username_of_client_socket[client_socket], client_socket);
              }
              else if (status_change_password_int == -2)
              {
                cout << "WRONG OLD PASSWORD" << endl;
                SendMessage(client_socket, "#wrong_change_info");
              }
              else if (status_change_password_int == -1)
              {
                SendMessage(client_socket, "#change_fail");
              }
            }
          }
          else if (option == "DELETE_ACCOUNT")
          {
            
            cout << "Start Delete account\n";
            if (login_status.find(client_socket)->second)
            {
              if (DeleteUser(username_of_client_socket[client_socket]) == 0)
              {
                cout << "DELETE SUCCESS\n";
                SendMessage(client_socket, "#delete_success");
                SendExitToClientsByUsername(username_of_client_socket[client_socket], client_socket);
              }
              else
              {
                cout << "DELETE FAILED\n";
                SendMessage(client_socket, "#delete_fail");
                SendExitToClientsByUsername(username_of_client_socket[client_socket], client_socket);
              }
            }
          }
          else if (option == "GET_LIST_ROOMS")
          {
            
            cout << "Start get list rooms\n";
            if (SendListToClient("room", username_of_client_socket[client_socket], client_socket) == 0)
            {
              cout << "HAVE ROOMS\n";
            }
            else
            {
              cout << "DONT HAVE ROOMS\n";
            }
          }
          else if (option == "GET_LIST_USERS")
          {
            
            cout << "Start Get list users\n";
            if (SendListToClient("user", username_of_client_socket[client_socket], client_socket) == 0)
            {
              cout << "HAVE USERS\n";
            }
            else
            {
              cout << "DONT HAVE USERS\n";
            }
          }
          else if (option == "CREATE_ROOM")
          {
            cout << "Start Create Room\n";
           
            string str = list_messages[1];
            if (CreateRoom(client_socket, str) == 0)
            {
              SendMessage(client_socket, "#room_create_success");
              cout << "CREATE ROOM SUCCESS\n";
            }
            else
            {
              SendMessage(client_socket, "#room_create_success");
              cout << "CREATE ROOM FAILED\n";
            }
          }
          else if (option == "CHAT")
          {
            cout << "Start Chat\n";
            
            
            string room_id = list_messages[1], input_chat = list_messages[2];
            cout << "room_id: " << room_id << "-- input_chat: " << input_chat << endl;
            SendMessage(client_socket, "#send_success");
            usleep(10000);
            SendMessageToClient(username_of_client_socket[client_socket], input_chat, client_socket, stoi(room_id));
          }
          else if (option == "OLD_MESSAGES")
          {
            string room_id = list_messages[1];
            cout << "Start Load Message\n";
            room_id_of_client_socket[client_socket] = stoi(room_id);
            cout << "room_id nao: " << room_id_of_client_socket[client_socket] << endl;

            LoadMessage(client_socket, stoi(room_id));
          } else if (option == "BACK") {
            cout << "Start Back\n";
            room_id_of_client_socket[client_socket] = -1;
          } else if (option == "EXIT_THREAD") {
            cout << "Start Exit Thread\n";
            room_id_of_client_socket.erase(client_socket);
            
            SendMessage(client_socket, option);
            
          } else if (option == "ROOM_SETTING") {
              string room_id = list_messages[1];
              cout << "Start Room Setting\n";
              if (!CheckRoomExisted(username_of_client_socket[client_socket], stoi(room_id)))
              {
                SendMessage(client_socket, "#exit_kick");
                
              } else {
              string check_admin_res = CheckAdmin(username_of_client_socket[client_socket], stoi(room_id)) ? "#admin" : "#member";
              cout << "check_admin_res: " << check_admin_res << endl;
              SendMessage(client_socket, check_admin_res);

              }
          } else if (option == "GET_LIST_USERS_OUT_THIS_ROOM") {
              string room_id = list_messages[1];
              cout << "Start get list user out this room\n";
              room_id_of_client_socket[client_socket] = stoi(room_id);
              if (!CheckRoomExisted(username_of_client_socket[client_socket], stoi(room_id)))
              {
                SendMessage(client_socket, "#exit_kick");
                
              } else {
                string outside_users;
                GetListUserOutSide(stoi(room_id), outside_users);
                cout << "outside_users: " << outside_users << endl;

                if (outside_users == "")
                  {
                    SendMessage(client_socket, "#no_user");
                  }
                else
                  {
                    SendMessage(client_socket, outside_users);
                  }
              }

          } else if (option == "ADD_USER") {
                cout << "Start Add User\n";
                string room_id = list_messages[1], list_users = list_messages[2];
                auto users = Split(list_users, seperator1);
                if (AddUserToRoom(stoi(room_id), users) == 0) {
                    SendMessage(client_socket, "#add_user_success");
                } else {
                    SendMessage(client_socket, "#add_user_fail");
                }
          } else if (option == "GET_LIST_USERS_IN_THIS_ROOM") {
                string room_id = list_messages[1];
                cout << "Start Get list users in this room\n";
                string inside_users;
                GetListUserInside(stoi(room_id), username_of_client_socket[client_socket], inside_users);
                if (inside_users == "") {
                  SendMessage(client_socket, "#no_user");
                } else {
                  SendMessage(client_socket, inside_users);

                }

          } else if (option == "KICK_USER") {
              cout << "Start Kick User\n";
              string room_id = list_messages[1], list_users = list_messages[2];
              auto users = Split(list_users, seperator1); 
              for (auto x: room_id_of_client_socket) {
                  if (x.second == stoi(room_id)) {
                    if (find(users.begin(), users.end(), username_of_client_socket[x.first]) != users.end()) {
                      SendMessage(x.first, "#exit_kick");
                    }
                  }
              }
            if (KickUserFromRoom(stoi(room_id), users) == 0) {
              SendMessage(client_socket, "#kick_user_success");
            } else 
            {
              SendMessage(client_socket,  "#kick_user_fail");
            }
          } else if (option == "MODIFY_ROOM_NAME") {
              string room_id = list_messages[1], new_room_name = list_messages[2];
              if (ModifyRoomName(stoi(room_id), new_room_name) == 0) {
                  SendMessage(client_socket, "#change_room_name_success" );
              } else {
                  SendMessage(client_socket,  "#change_room_name_fail" );
              }
          } 
          
        } else {
            string option_new = list_messages[1];
            if (option_new == "LOGIN") {
                cout << "Restart Login\n";
                string user_name = list_messages[2], password = list_messages[3];
                cout << user_name << ": " << password << endl;

                Login(client_socket, user_name, password);
            } else if (option_new == "#CLOSE") {
                cout << " CLOSE\n" << endl;
                clients_fds[i].fd = -1;
                EndConnection(client_socket);
                close(client_socket);
            } else if (option_new == "REGISTER") {
              cout << "Restart REGISTER\n";
              string user_name = list_messages[2], password = list_messages[3];
              cout << user_name << ": " << password << endl;
              Register(client_socket, user_name, password);
            } else if (option_new == "LOGOUT") {
              cout << "Restart LOGOUT\n";
              SendMessage(client_socket, "LOGOUT");
              login_status[client_socket] = false;
              username_of_client_socket[client_socket] = "";
            } else if (option_new == "CHANGE_PASSWORD") {
               cout << "Restart Change PassWord\n";
               login_status[client_socket] = true;
               username_of_client_socket[client_socket] = list_messages[4];
               if (login_status.find(client_socket)->second)
               {
                 string old_password = list_messages[2], new_password = list_messages[3];
                 cout << "old password: " << old_password << " , new password: " << new_password << endl;

                 int status_change_password_int =
                     ChangePassword(username_of_client_socket[client_socket], old_password, new_password);
                 if (status_change_password_int == 0)
                 {
                   cout << "CHANGE PASSWORD SUCCESS" << endl;
                   SendMessage(client_socket, "#change_success");

                   SendExitToClientsByUsername(username_of_client_socket[client_socket], client_socket);
                 }
                 else if (status_change_password_int == -2)
                 {
                   cout << "WRONG OLD PASSWORD" << endl;
                   SendMessage(client_socket, "#wrong_change_info");
                 }
                 else if (status_change_password_int == -1)
                 {
                   SendMessage(client_socket, "#change_fail");
                 }
               }
            } else if (option_new == "DELETE_ACCOUNT") {
              cout << "Restart Delete account\n";
              login_status[client_socket] = true;
              username_of_client_socket[client_socket] = list_messages[2];
              if (login_status.find(client_socket)->second)
              {
                if (DeleteUser(username_of_client_socket[client_socket]) == 0)
                {
                  cout << "DELETE SUCCESS\n";
                  SendMessage(client_socket, "#delete_success");
                  SendExitToClientsByUsername(username_of_client_socket[client_socket], client_socket);
                }
                else
                {
                  cout << "DELETE FAILED\n";
                  SendMessage(client_socket, "#delete_fail");
                  SendExitToClientsByUsername(username_of_client_socket[client_socket], client_socket);
                }
              }
            } else if (option_new == "BACK") {
                cout << "Restart Back\n";
                login_status[client_socket] = true;
                username_of_client_socket[client_socket] = list_messages[2];
                room_id_of_client_socket[client_socket] = -1;
            } else if (option_new == "EXIT_THREAD") {
                cout << "Restart EXIT_THREAD\n";
                login_status[client_socket] = true;
                username_of_client_socket[client_socket] = list_messages[2];
                room_id_of_client_socket.erase(client_socket);
                SendMessage(client_socket, option_new);
            } else if (option_new == "GET_LIST_ROOMS") {
                cout << "Restart get list rooms\n";
                login_status[client_socket] = true;
                username_of_client_socket[client_socket] = list_messages[2];
                if (SendListToClient("room", username_of_client_socket[client_socket], client_socket) == 0)
                {
                  cout << "HAVE ROOMS\n";
                }
                else
                {
                  cout << "DONT HAVE ROOMS\n";
                }
            } else if (option_new == "GET_LIST_USERS") {
                cout << "Restart get list users\n";
                login_status[client_socket] = true;
                username_of_client_socket[client_socket] = list_messages[2];
                if (SendListToClient("user", username_of_client_socket[client_socket], client_socket) == 0)
                {
                  cout << "HAVE USERS\n";
                }
                else
                {
                  cout << "DONT HAVE USERS\n";
                }
            } else if (option_new == "CREATE_ROOM") {
                cout << "Restart Create Room\n";
                login_status[client_socket] = true;
                username_of_client_socket[client_socket] = list_messages[3];
                string str = list_messages[2];
                if (CreateRoom(client_socket, str) == 0)
                {
                  SendMessage(client_socket, "#room_create_success");
                  cout << "CREATE ROOM SUCCESS\n";
                }
                else
                { 
                  SendMessage(client_socket, "#room_create_success");
                  cout << "CREATE ROOM FAILED\n";
                }
            } else if (option_new == "OLD_MESSAGES") {
                cout << "Restart Load Message\n";
                login_status[client_socket] = true;
                username_of_client_socket[client_socket] = list_messages[3];
                string room_id = list_messages[2];
                room_id_of_client_socket[client_socket] = stoi(room_id);
                cout << "room_id nao: " << room_id_of_client_socket[client_socket] << endl;

                LoadMessage(client_socket, stoi(room_id));
            } else if (option_new == "CHAT") {
              cout << "Restart Chat\n";
              login_status[client_socket] = true;
              username_of_client_socket[client_socket] = list_messages[4];
              string room_id = list_messages[2], input_chat = list_messages[3];
              cout << "room_id: " << room_id << "-- input_chat: " << input_chat << endl;
              SendMessage(client_socket, "#send_success");
              usleep(10000);
              SendMessageToClient(username_of_client_socket[client_socket], input_chat, client_socket, stoi(room_id));
            } else if (option_new == "ROOM_SETTING") {
              cout << "Restart Room Setting\n";
              string room_id = list_messages[2];
              login_status[client_socket] = true;
              username_of_client_socket[client_socket] = list_messages[3];
              if (!CheckRoomExisted(username_of_client_socket[client_socket], stoi(room_id)))
              {
                SendMessage(client_socket, "#exit_kick");
                
              } else {
              string check_admin_res = CheckAdmin(username_of_client_socket[client_socket], stoi(room_id)) ? "#admin" : "#member";
              cout << "check_admin_res: " << check_admin_res << endl;
              SendMessage(client_socket, check_admin_res);

              }
            } else if (option_new == "GET_LIST_USERS_OUT_THIS_ROOM") {
             
              cout << "Restart get list user out this room\n";
              login_status[client_socket] = true;
              string room_id = list_messages[2];
              username_of_client_socket[client_socket] = list_messages[3];
              // room_id_of_client_socket[client_socket] = stoi(room_id);
              if (!CheckRoomExisted(username_of_client_socket[client_socket], stoi(room_id)))
              {
                SendMessage(client_socket, "#exit_kick");
                
              } else {
                string outside_users;
                GetListUserOutSide(stoi(room_id), outside_users);
                cout << "outside_users: " << outside_users << endl;

                if (outside_users == "")
                  {
                    SendMessage(client_socket, "#no_user");
                  }
                else
                  {
                    SendMessage(client_socket, outside_users);
                  }
              }
            } else if (option_new == "ADD_USER") {
              cout << "Restart Add User\n";
              string room_id = list_messages[2], list_users = list_messages[3];
              login_status[client_socket] = true;

              username_of_client_socket[client_socket] = list_messages[4];
              // room_id_of_client_socket[cliet_socket] = stoi(room_id);
              auto users = Split(list_users, seperator1);
              if (AddUserToRoom(stoi(room_id), users) == 0)
              {
                SendMessage(client_socket, "#add_user_success");
              }
              else
              {
                SendMessage(client_socket, "#add_user_fail");
              }
            } else if (option_new == "GET_LIST_USERS_IN_THIS_ROOM") {
              
              cout << "Restart Get list users in this room\n";
              string inside_users;
              string room_id = list_messages[2];
              login_status[client_socket] = true;
              username_of_client_socket[client_socket] = list_messages[3];
              GetListUserInside(stoi(room_id), username_of_client_socket[client_socket], inside_users);
              if (inside_users == "")
              {
                SendMessage(client_socket, "#no_user");
              }
              else
              {
                SendMessage(client_socket, inside_users);
              } 
            } else if (option_new == "KICK_USER") {
              cout << "Restart Kick User\n";
              login_status[client_socket] = true;
              username_of_client_socket[client_socket] = list_messages[4];
              string room_id = list_messages[2], list_users = list_messages[3];
              auto users = Split(list_users, seperator1); 
              for (auto x: room_id_of_client_socket) {
                  if (x.second == stoi(room_id)) {
                    if (find(users.begin(), users.end(), username_of_client_socket[x.first]) != users.end()) {
                      SendMessage(x.first, "#exit_kick");
                    }
                  }
              }
            if (KickUserFromRoom(stoi(room_id), users) == 0) {
              SendMessage(client_socket, "#kick_user_success");
            } else 
            {
              SendMessage(client_socket,  "#kick_user_fail");
            }
            } else if (option_new == "MODIFY_ROOM_NAME") {
              cout << "Restart Modify room name\n";
              login_status[client_socket] = true;
              username_of_client_socket[client_socket] = list_messages[4];
              string room_id = list_messages[2], new_room_name = list_messages[3];
              if (ModifyRoomName(stoi(room_id), new_room_name) == 0) {
                  SendMessage(client_socket, "#change_room_name_success" );
              } else {
                  SendMessage(client_socket,  "#change_room_name_fail" );
              }
            } else if (option_new == "EMPTY") {
              cout << "Restart room \n";
              string room_id = list_messages[3];
              login_status[client_socket] = true;
              username_of_client_socket[client_socket] = list_messages[2];
              room_id_of_client_socket[client_socket] = stoi(room_id);
            }
        }
      }
    }
  } while (1);

  return close(this->server_socket);
}
int Server::ModifyRoomName(int room_id, string new_name) {
  sql::Driver *driver;
  sql::Connection *con;
  sql::PreparedStatement *prep_stmt;

  driver = get_driver_instance();
  con =
      driver->connect(string(getenv("MYSQL_CONT_NAME")) + ":3306", "root", "1");
  con->setSchema("CHAT_SERVICE");
  string query =
      string("UPDATE ROOM ") + string("SET name = ? ") + string("WHERE id = ?");
  prep_stmt = con->prepareStatement(query);
  prep_stmt->setString(1, new_name);
  prep_stmt->setInt(2, room_id);
  if (prep_stmt->executeUpdate() > 0) {
    delete prep_stmt;
    delete con;
    return 0;
  } else {
    delete prep_stmt;
    delete con;
    return -1;
  }
}


int Server::AddUserToRoom(int room_id, vector<string> users) {
  try {
    sql::Driver *driver;
    sql::Connection *con;
    sql::PreparedStatement *prep_stmt;

    driver = get_driver_instance();
    con =
        driver->connect(string(getenv("MYSQL_CONT_NAME")) + ":3306", "root", "1");
    con->setSchema("CHAT_SERVICE");
    for (int i = 0; i < users.size(); i++) {
          string query =
              string("INSERT INTO PARTICIPATION ") + string("VALUES(?, ?)");
          prep_stmt = con->prepareStatement(query);
          prep_stmt->setString(1, users[i]);
          prep_stmt->setInt(2, room_id);
          prep_stmt->executeUpdate();
        }
    
    delete con;
    delete prep_stmt;
    return 0;
  }
  catch (...)
  {
    return -1;
  }
}

int Server::GetListUserOutSide(int room_id,  string &list) {
  sql::Driver *driver;
  sql::Connection *con;
  sql::PreparedStatement *prep_stmt;
  sql::ResultSet *res;
  driver = get_driver_instance();
  con =
      driver->connect(string(getenv("MYSQL_CONT_NAME")) + ":3306", "root", "1");
  con->setSchema("CHAT_SERVICE");
  string query = string("SELECT username ") +
                 string("FROM USER WHERE is_deleted = false AND ") +
                 string(
                     "username NOT IN (SELECT username FROM PARTICIPATION "
                     "WHERE room_id = ?)");
  prep_stmt = con->prepareStatement(query);
  prep_stmt->setInt(1, room_id);
  res = prep_stmt->executeQuery();
  while (res->next()) {
    list += res->getString(1) + "~";
  }
  delete con;
  delete prep_stmt;
  delete res;
  if (list != "") {
    return 0;
  } else {
    return -1;
  }

}
// Broadcast message to all clients except the sender
int Server::BroadcastMessage(string message, int sender_id, int room_id)
{

  cout << "Bat dau gui tin nhan\n";

  cout << "room_id_of_client_socket size: " << room_id_of_client_socket.size() << endl;

  for (auto x: room_id_of_client_socket) {
    cout << x.first << " access room id: " << x.second << endl;
    if (x.second == room_id && x.first!= sender_id) {
      cout << "gui den: " << username_of_client_socket[x.first]<< endl;
      int status = SendMessage(x.first, message);
      cout << "status: " << status << endl;

    }

  }
  cout <<"Het gui \n";
}

bool Server::CheckRoomExisted(string username, int room_id) {
  sql::Driver *driver;
  sql::Connection *con;
  sql::Statement *stmt;
  sql::ResultSet *res;
  sql::PreparedStatement *prep_stmt;
  driver = get_driver_instance();
  con =
      driver->connect(string(getenv("MYSQL_CONT_NAME")) + ":3306", "root", "1");
  con->setSchema("CHAT_SERVICE");
  stmt = con->createStatement();
  stmt->execute("USE CHAT_SERVICE");
  prep_stmt = con->prepareStatement(
    string("SELECT * FROM PARTICIPATION WHERE username = ? ") +
    "AND room_id = ?");
  prep_stmt->setString(1, username);
  prep_stmt->setInt(2, room_id);
  res = prep_stmt->executeQuery();

  if (res->next()) {
    return true;
  }

  return false;
}
int Server::KickUserFromRoom(int room_id, vector<string> users) {
  try {
    sql::Driver *driver;
    sql::Connection *con;
    sql::PreparedStatement *prep_stmt;

    driver = get_driver_instance();
    con =
        driver->connect(string(getenv("MYSQL_CONT_NAME")) + ":3306", "root", "1");
    con->setSchema("CHAT_SERVICE");
    for (int i = 0; i < users.size(); i++) {
    string query = string("DELETE FROM PARTICIPATION ") +
                  string("WHERE room_id = ? AND username = ?");
          prep_stmt = con->prepareStatement(query);
          prep_stmt->setInt(1, room_id);
          prep_stmt->setString(2, users[i]);
          prep_stmt->executeUpdate();
        }
    
    delete con;
    delete prep_stmt;
    return 0;
  }
  catch (...) { return -1; }
}
bool Server::CheckAdmin(string user_name, int room_id) {
  sql::Driver *driver;
  sql::Connection *con;
  sql::PreparedStatement *prep_stmt;
  sql::ResultSet *res;

  driver = get_driver_instance();
  con =
      driver->connect(string(getenv("MYSQL_CONT_NAME")) + ":3306", "root", "1");
  con->setSchema("CHAT_SERVICE");
  string query = string("SELECT id ") + string("FROM ROOM ") +
                 string("WHERE admin = ? AND id = ?");
  prep_stmt = con->prepareStatement(query);
  prep_stmt->setString(1, user_name);
  prep_stmt->setInt(2, room_id);
  res = prep_stmt->executeQuery();
  if(res->next()) {
    delete prep_stmt;
    delete con;
    delete res;
    return true;
  }
  delete prep_stmt;
  delete con;
  delete res;
  return false;
}


int Server::CreateRoom(int client_socket, string str)
{
  vector<string> split_room_and_username = Split(str, seperator2);
  vector<string> members = Split(split_room_and_username[0], seperator1);
  members.push_back(username_of_client_socket[client_socket]);
  int room_id;
  if (members.size() == 2)
  {
    room_id =
        Server::InitChatOneOne(username_of_client_socket[client_socket], members[0]);
  }
  else
  {
    room_id = Server::InitChatRoom(split_room_and_username[1], members);
  }
  if (room_id > 0)
  {
    cout << "CREATE ROOM SUCCESS\n";
    return 0;
  }
  else
  {
    cout << "CREATE ROOM FALIED\n";
    return -1;
  }
}
vector<string> Server::SplitString(string str, string del)
{
  int start, end = -1 * del.size();
  vector<string> result;
  do
  {
    start = end + del.size();
    end = str.find(del, start);
    cout << str.substr(start, end - start) << endl;
    result.push_back(str.substr(start, end - start));
  } while (end != -1);
  return result;
}
int Server::Register(int client_socket, string user_name, string password)
{

  if (CheckRegister(user_name) == 0)
  {
    // had a account in database
    string message = "#register_fail";
    cout << user_name << "register failed, account existed" << endl;
    SendMessage(client_socket, message);

    return -1;
  }
  else
  {
    if (CreateAccount(user_name, password) == 0)
    {
      string message = "#register_success";
      cout << user_name << " register success" << endl;

      SendMessage(client_socket, message);

      return 0;
    }
    else
    {
      // insert error
      string message = "#register_fail";
      cout << user_name << " register failed, insert error" << endl;
      SendMessage(client_socket, message);
      return -1;
    }
  }
}
int Server::Login(int client_socket, string user_name, string password)
{

  if (CheckLogin(user_name, password) == 0)
  {

    cout << user_name << " log in success" << endl;
    string message = "#login_success";

    SendMessage(client_socket, message);
    login_status[client_socket] = true;
    username_of_client_socket[client_socket] = user_name;
    return 0;
  }
  else
  {
    string message = "#login_fail";
    cout << user_name << " log in failed" << endl;
    SendMessage(client_socket, message);
    return 0;
  }
}
int Server::CreateAccount(string user_name, string password)
{
  sql::Driver *driver;
  sql::Connection *con;
  sql::Statement *stmt;
  sql::PreparedStatement *prep_stmt;
  driver = get_driver_instance();
  con =
      driver->connect(string(getenv("MYSQL_CONT_NAME")) + ":3306", "root", "1");
  con->setSchema("CHAT_SERVICE");
  stmt = con->createStatement();
  stmt->execute("USE CHAT_SERVICE");
  prep_stmt = con->prepareStatement(
      "INSERT INTO USER(username, name, password, color_id) VALUES (?, ?, "
      "SHA2(?, "
      "256), ?)");
  prep_stmt->setString(1, user_name);
  prep_stmt->setString(2, user_name);
  prep_stmt->setString(3, password);
  prep_stmt->setInt(
      4, rand() % static_cast<int>(sizeof(colors) / sizeof(colors[0])));
  int flag = prep_stmt->executeUpdate();
  if (flag == 1)
  {
    cout << "insert success with username " << user_name << "\n";
    delete stmt;
    delete prep_stmt;
    delete con;
    return 0;
  }
  else if (flag == 0)
  {
    cout << "insert failed \n";
    delete stmt;
    delete prep_stmt;
    delete con;
    return -1;
  }
}
int Server::CheckRegister(string user_name)
{
  sql::Driver *driver;
  sql::Connection *con;
  sql::Statement *stmt;
  sql::ResultSet *res;
  sql::PreparedStatement *prep_stmt;
  driver = get_driver_instance();
  con =
      driver->connect(string(getenv("MYSQL_CONT_NAME")) + ":3306", "root", "1");
  con->setSchema("CHAT_SERVICE");
  stmt = con->createStatement();
  stmt->execute("USE CHAT_SERVICE");
  cout << "username: " << user_name << endl;
  prep_stmt = con->prepareStatement("SELECT * FROM USER WHERE BINARY username=?");
  prep_stmt->setString(1, user_name);

  res = prep_stmt->executeQuery();
  int flag = 1;
  if (res->next() == 1)
  {
    flag = 0;
  }
  else
  {
    flag = 1;
  }
  if (flag == 0)
  {
    cout << "can't register" << endl;
    delete res;
    delete stmt;
    delete con;
    return 0;
  }
  else if (flag == 1)
  {
    cout << "start register" << endl;
    delete res;
    delete stmt;
    delete con;
    return -1;
  }
}
int Server::CheckLogin(string user_name, string password)
{
  sql::Driver *driver;
  sql::Connection *con;
  sql::Statement *stmt;
  sql::ResultSet *res;
  sql::PreparedStatement *prep_stmt;
  driver = get_driver_instance();
  con =
      driver->connect(string(getenv("MYSQL_CONT_NAME")) + ":3306", "root", "1");
  con->setSchema("CHAT_SERVICE");
  stmt = con->createStatement();
  stmt->execute("USE CHAT_SERVICE");
  cout << "user name in login " << user_name << endl;
  prep_stmt = con->prepareStatement(
      "SELECT * FROM USER WHERE BINARY username=? AND BINARY password=SHA2(?,256) AND "
      "is_deleted=false");
  prep_stmt->setString(1, user_name);
  prep_stmt->setString(2, password);
  res = prep_stmt->executeQuery();
  int flag = 1;
  if (res->next() == 1)
  {
    flag = 0;
  }
  else
  {
    flag = 1;
  }
  if (flag == 0)
  {
    cout << "login success" << endl;
    delete res;
    delete stmt;
    delete con;
    return 0;
  }
  else if (flag == 1)
  {
    cout << "wrong password" << endl;
    delete res;
    delete stmt;
    delete con;
    return -1;
  }
}

string Server::GetColor(int code) { return colors[code % NUM_COLORS]; }

int Server::SendMessageToClient(string username, string message,
                                int client_socket, int room_id)
{

  // SendMessage(client_socket, "#SEND_SUCCESS");
  SaveMessage(username, room_id, message);
  SharedPrint(username + " : " + message);
  BroadcastMessage(username + " : " + message,
                   client_socket, room_id);
}

// Set username of client
int Server::SetName(int id, char username[])
{

  return -1;
}

// For synchronisation of cout statements
int Server::SharedPrint(string str, bool end_line)
{
  cout << str;
  if (end_line)
    cout << endl;
  return 0;
}

int Server::GetListUserInside(int room_id, string username, string &list) {
  sql::Driver *driver;
  sql::Connection *con;
  sql::PreparedStatement *prep_stmt;
  sql::ResultSet *res;
  driver = get_driver_instance();
  con =
      driver->connect(string(getenv("MYSQL_CONT_NAME")) + ":3306", "root", "1");
  con->setSchema("CHAT_SERVICE");
  string query =
      string("SELECT username ") +
      string("FROM USER WHERE is_deleted = false AND NOT username = ? AND ") +
      string(
          "username IN (SELECT username FROM PARTICIPATION WHERE room_id = ?)");
  prep_stmt = con->prepareStatement(query);
  prep_stmt->setString(1, username);
  prep_stmt->setInt(2, room_id);
  res = prep_stmt->executeQuery();
  while (res->next()) {
    list += res->getString(1) + "~";
  }
  delete con;
  delete prep_stmt;
  delete res;
  if (list != "") {
    return 0;
  } else {
    return -1;
  }
}


// Broadcast a number to all clients except the sender
int Server::BroadcastMessage(int num, int sender_id, int room_id)
{
  // for (int i = 0; i < this->clients.size(); i++) {
  //   if (this->clients[i].socket != sender_id && this->clients[i].success == 0 &&
  //       this->clients[i].room_id == room_id) {
  //     SendMessage(this->clients[i].socket, to_string(num));
  //   }
  // }
}

int Server::EndConnection(int id)
{
  login_status.erase(id);
  username_of_client_socket.erase(id);
  room_id_of_client_socket.erase(id);
  return -1;
}

int Server::SaveMessage(string user_name, int room_id, string content)
{
  sql::Driver *driver;
  sql::Connection *con;
  sql::PreparedStatement *prep_stmt;

  driver = get_driver_instance();
  con =
      driver->connect(string(getenv("MYSQL_CONT_NAME")) + ":3306", "root", "1");
  con->setSchema("CHAT_SERVICE");
  string query = string("INSERT INTO ") +
                 string("MESSAGE(username, room_id, content, time) ") +
                 string("VALUES(?, ?, ?, now())");
  prep_stmt = con->prepareStatement(query);
  prep_stmt->setString(1, user_name);
  prep_stmt->setInt(2, room_id);
  prep_stmt->setString(3, content);
  if (prep_stmt->executeUpdate() > 0)
  {
    delete prep_stmt;
    delete con;
    return 0;
  }
  else
  {
    delete prep_stmt;
    delete con;
    return -1;
  }
}

int Server::LoadMessage(int client_id, int room_id, int day)
{
  sql::Driver *driver;
  sql::Connection *con;
  sql::PreparedStatement *prep_stmt;
  sql::ResultSet *res;
  driver = get_driver_instance();
  con =
      driver->connect(string(getenv("MYSQL_CONT_NAME")) + ":3306", "root", "1");
  con->setSchema("CHAT_SERVICE");
  string query =
      string("SELECT M.username, content ") +
      string("FROM MESSAGE M JOIN USER U ON M.username = U.username ") +
      string("WHERE room_id = ? AND DATEDIFF(NOW(), time) <=? ") +
      string("ORDER BY M.id ASC");
  prep_stmt = con->prepareStatement(query);

  prep_stmt->setInt(1, room_id);
  prep_stmt->setInt(2, day);
  res = prep_stmt->executeQuery();
  string old_message = "";
  int color = 1;
  string tmp_user = "";
  while (res->next())
  {
    if (tmp_user == "" && color == 1)
    {
      tmp_user = res->getString(1);
    }
    if (res->getString(1) != tmp_user)
    {
      tmp_user = res->getString(1);
      color++;
    }
    old_message += 
                   res->getString(1) + ":" + res->getString(2) +
                   hash;
  }

  SharedPrint(old_message);
  if (old_message.size() == 0)
  {
    SendMessage(client_id, "No message!");
  }
  else
  {
    SendMessage(client_id, old_message);
  }
  delete prep_stmt;
  delete con;
  delete res;
  return 0;
}

int Server::ModifyName(string user_name, string new_name)
{
  sql::Driver *driver;
  sql::Connection *con;
  sql::PreparedStatement *prep_stmt;
  sql::ResultSet *res;

  driver = get_driver_instance();
  con =
      driver->connect(string(getenv("MYSQL_CONT_NAME")) + ":3306", "root", "1");
  con->setSchema("CHAT_SERVICE");
  string query = string("UPDATE USER ") + string("SET name = ? ") +
                 string("WHERE username = ?");
  prep_stmt = con->prepareStatement(query);
  prep_stmt->setString(1, new_name);
  prep_stmt->setString(2, user_name);
  if (prep_stmt->executeUpdate() > 0)
  {
    delete prep_stmt;
    delete con;
    delete res;
    return 0;
  }
  else
  {
    delete prep_stmt;
    delete con;
    delete res;
    return -1;
  }
}

int Server::ChangePassword(string user_name, string old_password,
                           string new_password)
{
  sql::Driver *driver;
  sql::Connection *con;
  sql::PreparedStatement *prep_stmt;
  sql::ResultSet *res;
  driver = get_driver_instance();
  con =
      driver->connect(string(getenv("MYSQL_CONT_NAME")) + ":3306", "root", "1");
  con->setSchema("CHAT_SERVICE");

  string query = string("SELECT * ") + string("FROM USER ") +
                 string("WHERE BINARY username = ? AND BINARY password = SHA2(?,256)");
  prep_stmt = con->prepareStatement(query);
  prep_stmt->setString(1, user_name);
  prep_stmt->setString(2, old_password);
  res = prep_stmt->executeQuery();
  if (res->next() != 1)
  {
    return -2; // wrong password
  }
  query = string("UPDATE USER ") + string("SET password = SHA2(?,256) ") +
          string("WHERE username = ?");
  prep_stmt = con->prepareStatement(query);
  prep_stmt->setString(1, new_password);
  prep_stmt->setString(2, user_name);
  if (prep_stmt->executeUpdate() > 0)
  {

    delete prep_stmt;
    delete con;
    delete res;
    return 0;
  }
  else
  {
    delete prep_stmt;
    delete con;
    delete res;
    return -1;
  }
}

int Server::DeleteUser(string user_name)
{
  sql::Driver *driver;
  sql::Connection *con;
  sql::PreparedStatement *prep_stmt;
  sql::ResultSet *res;

  driver = get_driver_instance();
  con =
      driver->connect(string(getenv("MYSQL_CONT_NAME")) + ":3306", "root", "1");
  con->setSchema("CHAT_SERVICE");
  string query = string("UPDATE USER ") + string("SET is_deleted = true ") +
                 string("WHERE username = ?");
  prep_stmt = con->prepareStatement(query);
  prep_stmt->setString(1, user_name);
  if (prep_stmt->executeUpdate() > 0)
  {
    delete prep_stmt;
    delete con;

    return 0;
  }
  else
  {
    delete prep_stmt;
    delete con;
    return -1;
  }
}

int Server::GetListRoom(string username, string &list)
{
  sql::Driver *driver;
  sql::Connection *con;
  sql::PreparedStatement *prep_stmt;
  sql::ResultSet *res;
  driver = get_driver_instance();
  con =
      driver->connect(string(getenv("MYSQL_CONT_NAME")) + ":3306", "root", "1");
  con->setSchema("CHAT_SERVICE");
  string query =
      string("SELECT id, name ") + string("FROM ROOM ") +
      string("WHERE id IN ") +
      string("(SELECT room_id FROM PARTICIPATION WHERE BINARY username =?)");
  prep_stmt = con->prepareStatement(query);
  prep_stmt->setString(1, username);
  res = prep_stmt->executeQuery();
  while (res->next())
  {
    list += to_string(res->getInt(1)) + "`" + res->getString(2) + "~";
  }
  delete con;
  delete prep_stmt;
  delete res;
  if (list != "")
  {
    return 0;
  }
  else
  {
    return -1;
  }
}

int Server::GetListUser(string username, string &list)
{
  sql::Driver *driver;
  sql::Connection *con;
  sql::PreparedStatement *prep_stmt;
  sql::ResultSet *res;
  driver = get_driver_instance();
  con =
      driver->connect(string(getenv("MYSQL_CONT_NAME")) + ":3306", "root", "1");
  con->setSchema("CHAT_SERVICE");
  string query =
      string("SELECT username ") +
      string("FROM USER WHERE is_deleted = false AND NOT username =?");
  prep_stmt = con->prepareStatement(query);
  prep_stmt->setString(1, username);
  res = prep_stmt->executeQuery();
  while (res->next())
  {
    list += res->getString(1) + "~";
  }
  delete con;
  delete prep_stmt;
  delete res;
  if (list != "")
  {
    return 0;
  }
  else
  {
    return -1;
  }
}

int Server::SendListToClient(string flag, string username, int client_id)
{
  string list = "";
  int get_successful;
  if (flag == "room")
  {
    get_successful = GetListRoom(username, list);
  }
  else
  {
    get_successful = GetListUser(username, list);
  }
  char list_char[MAX_LEN];
  if (get_successful < 0)
  {
    if (flag == "room")
    {
      SendMessage(client_id, "#no_room");
    }
    else
    {
      SendMessage(client_id, "#no_user");
    }
    return -1;
  }
  else
  { // have users, rooms
    SendMessage(client_id, list);
    return 0;
  }
}

int Server::InitChatOneOne(string user_1, string user_2)
{
  sql::Driver *driver;
  sql::Connection *con;
  sql::PreparedStatement *prep_stmt;
  sql::ResultSet *res;
  sql::ConnectOptionsMap connection_properties;

  driver = get_driver_instance();
  con =
      driver->connect(string(getenv("MYSQL_CONT_NAME")) + ":3306", "root", "1");
  con->setSchema("CHAT_SERVICE");
  string query = string("SELECT id ") + string("FROM ROOM ") +
                 string("WHERE count = 2 AND is_chat_room = false ") +
                 string(
                     "AND id IN (SELECT room_id AS id FROM PARTICIPATION WHERE "
                     "username = ?) ") +
                 string(
                     "AND id IN (SELECT room_id AS id FROM PARTICIPATION WHERE "
                     "username = ?)");
  prep_stmt = con->prepareStatement(query);
  prep_stmt->setString(1, user_1);
  prep_stmt->setString(2, user_2);
  res = prep_stmt->executeQuery();
  int room_id = 0;

  while (res->next()) {
    room_id = res->getInt(1);
  }
  if (room_id == 0) {
    // room does not exist
    
    query = "SELECT func_create_room_1_1(?, ?)";
    prep_stmt = con->prepareStatement(query);
    prep_stmt->setString(1, user_1);
    prep_stmt->setString(2, user_2);
    res = prep_stmt->executeQuery();
    while (res->next()) {
      room_id = res->getInt(1);
    }
  }
  return room_id;
}

int Server::InitChatRoom(string room_name, vector<string> members) {
  sql::Driver *driver;
  sql::Connection *con;
  sql::PreparedStatement *prep_stmt;
  sql::ResultSet *res;
  sql::ConnectOptionsMap connection_properties;

  driver = get_driver_instance();
  con =
      driver->connect(string(getenv("MYSQL_CONT_NAME")) + ":3306", "root", "1");
  con->setSchema("CHAT_SERVICE");
  string query =
            string("INSERT INTO ROOM(name, count, admin, is_chat_room) ") + string("VALUES(?, ?, ?, true)");
  prep_stmt = con->prepareStatement(query);
  prep_stmt->setString(1, room_name);
  prep_stmt->setInt(2, members.size());
  prep_stmt->setString(3, members[members.size() - 1]);
  if (prep_stmt->executeUpdate() > 0) {
    query = string("SELECT id FROM ROOM ") +
            string("WHERE name = ? AND count = ? AND is_chat_room = true ") +
            string("ORDER BY id DESC ") + 
            string("LIMIT 1");
    prep_stmt = con->prepareStatement(query);
    prep_stmt->setString(1, room_name);
    prep_stmt->setInt(2, members.size());
    res = prep_stmt->executeQuery();
    int room_id = 0;
    while (res->next()) {
      room_id = res->getInt(1);
    }
    if (room_id != 0) {
      for (int i = 0; i < members.size(); i++) {
        string query =
            string("INSERT INTO PARTICIPATION ") + string("VALUES(?, ?)");
        prep_stmt = con->prepareStatement(query);
        prep_stmt->setString(1, members[i]);
        prep_stmt->setInt(2, room_id);
        prep_stmt->executeUpdate();
      }
    } else {
      return -1;
    }
    return room_id;
  } else {
    return -1;
  }
}

vector<string> Server::Split(string str, char seperator)
{
  vector<string> splitted;
  int i = 0;
  int startIndex = 0, endIndex = 0;
  while (i <= str.size())
  {
    if (str[i] == seperator || i == str.size())
    {
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

int Server::GetColorIdByUsername(string user_name)
{
  sql::Driver *driver;
  sql::Connection *con;
  sql::PreparedStatement *prep_stmt;
  sql::ResultSet *res;

  driver = get_driver_instance();
  con =
      driver->connect(string(getenv("MYSQL_CONT_NAME")) + ":3306", "root", "1");
  con->setSchema("CHAT_SERVICE");
  string query =
      string("SELECT color_id FROM USER ") + string("WHERE username = ?");
  prep_stmt = con->prepareStatement(query);
  prep_stmt->setString(1, user_name);
  res = prep_stmt->executeQuery();
  while (res->next())
  {
    return res->getInt(1);
  }
}

int Server::SendExitToClientsByUsername(string username, int client_socket)
{
  for (auto x : username_of_client_socket)
  {
    cout << x.second << "----" << x.first << endl;
    if (x.second == username)
    {
      if (x.first != client_socket)
      {
        cout << "gui #exit " << x.first << endl;
        SendMessage(x.first, "#exit");
      }

      login_status[x.first] = false;
      username_of_client_socket[x.first] = "";
    }
  }
}

int Server::SendMessage(int client_socket, string message)
{
  return send(client_socket, message.c_str(), message.size() + 1, MSG_CONFIRM);
}

pair<int, string> Server::RecvMessage(int client_socket)
{
  char str[MAX_LEN];
  memset(str, 0, sizeof(str));
  int byte = recv(client_socket, str, sizeof(str), 0);
  string message = string(str);
  return make_pair(byte, message);
}
