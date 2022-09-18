#include "clientQT.h"
#include "ui_clientQT.h"
#include "recvthread.h"
ClientQT::ClientQT(QWidget *parent) : QWidget(parent),
                                      ui(new Ui::ClientQT)
{
    ui->setupUi(this);
    
    client.CreateSocket();
    ConnectServer();

    ui->stackedWidget->setCurrentWidget(ui->authentication);
    ui->list_users_CreateRoom->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->list_users_CreateRoom->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->list_users_CreateRoom->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    QString image_link = ":/image/jisoo_resize.png";
    ui->stackedWidget->setStyleSheet(".QWidget{background-image:url(" + image_link + ")}");

    current_room_id = "";
    ui->list_rooms_listWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // recvMessage = NULL;
    recvMessage = new RecvThread(this,this);
    ui->waiting_label->setVisible(false);
    connect(recvMessage, &RecvThread::finished, recvMessage, &QObject::deleteLater);
    // connect(recvMessage,SIGNAL(NewMessage(string)), this, SLOT(OnNewMessage(string)));
    // connect(recvMessage, SIGNAL(finished()), this, SLOT(Quit()));
//    ui->confirm_login_button->setDefault(true);
    ui->list_messages_listWidget->scrollToBottom();

}
void ClientQT::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Return) {
        if (ui->stackedWidget->currentWidget() == ui->Login) {
            ui->confirm_login_button->clicked();
        } else if (ui->stackedWidget->currentWidget() == ui->Register ) {
            ui->confirm_register_button->clicked();
        } else if (ui->stackedWidget->currentWidget() == ui->ChooseRoom) {
            ui->send_message_button->clicked();
        } else if (ui->stackedWidget->currentWidget() == ui->AddUser ) {
            ui->confirm_AddUser->clicked();
        } else if (ui->stackedWidget->currentWidget() == ui->ChangePassword) {
            ui->change_button_ChangePassword->clicked();
        } else if (ui->stackedWidget->currentWidget() == ui->KickUser) {
            ui->confirm_KickUser->clicked();
        } else if (ui->stackedWidget->currentWidget() == ui->ChangeRoomName) {
            ui->confirm_ChangeRoomName->clicked();
        }

    }
}
ClientQT::~ClientQT()
{
    delete ui;
}

// Authentication menu Widget
void ClientQT::on_register_button_authentication_clicked()
{

    ui->username_input_Register->setText("");
    ui->password_input_Register->setText("");
    ui->retype_password_input_Register->setText("");
    ui->stackedWidget->setCurrentWidget(ui->Register);
}
void ClientQT::on_login_button_authentication_clicked()
{

    ui->username_input_login->setText("");
    ui->password_input_login->setText("");
    ui->stackedWidget->setCurrentWidget(ui->Login);
}

void ClientQT::on_exit_button_authentication_clicked()
{
    vector<string> message;
    message.push_back("#CLOSE");
    // client.SendMessage(SendHashMessage(message));
    SendMessage(message);
    client.CloseConnection();
    close();
}
// Register Widget
void ClientQT::on_back_button_Register_clicked()
{

    ui->stackedWidget->setCurrentWidget(ui->authentication);
}
void ClientQT::on_confirm_register_button_clicked()
{
    string username = ui->username_input_Register->text().toStdString();
    if (username.size() == 0)
    {
        QMessageBox msgBox;
        msgBox.setText("Username can't be empty");
        msgBox.exec();
        return;
    }
    string password = ui->password_input_Register->text().toStdString();
    if (password.size() == 0)
    {
        QMessageBox msgBox;
        msgBox.setText("Password can't be empty");
        msgBox.exec();
        return;
    }
    string retype_password = ui->retype_password_input_Register->text().toStdString();
    if (retype_password.size() ==0) {
        QMessageBox msgBox;
        msgBox.setText("Retype Password can't be empty");
        msgBox.exec();
        return;
    }
    if (password != retype_password) {
        QMessageBox msgBox;
        msgBox.setText("Retype password isn't match!");
        ui->retype_password_input_Register->setText("");

        msgBox.exec();
        return;
    }
    vector<string> send_message;
    send_message.push_back("REGISTER");
    send_message.push_back(username);
    send_message.push_back(password);

    // client.SendMessage(SendHashMessage(send_message));
    SendMessage(send_message);
    string check = RecvMessage(send_message).second;
    
    if (check == "#register_fail")
    {
        QMessageBox msgBox;
        msgBox.setText("Register failed!");
        msgBox.exec();
    }
    else if (check == "#register_success")
    {
        QMessageBox msgBox;
        msgBox.setText("Account registered");
        msgBox.exec();
    }
    ui->stackedWidget->setCurrentWidget(ui->authentication);
}
// Login Widget
string ClientQT::SendHashMessage(vector<string> list_messages)
{
    string result = "";
    for (int i = 0; i < list_messages.size() - 1; i++)
    {
        result += list_messages[i] + hash;
    }
    result += list_messages[list_messages.size() - 1];
    return result;
}
void ClientQT::on_back_button_login_clicked()
{

    ui->stackedWidget->setCurrentWidget(ui->authentication);
}
void ClientQT::on_confirm_login_button_clicked()
{

    // Check if username input empty
    string username = ui->username_input_login->text().toStdString();
    if (username.size() == 0)
    {
        QMessageBox msgBox;
        msgBox.setText("Username can't be empty");
        msgBox.exec();
        return;
    }
    string password = ui->password_input_login->text().toStdString();
    if (password.size() == 0)
    {
        QMessageBox msgBox;
        msgBox.setText("Password can't be empty");
        msgBox.exec();
        return;
    }
    vector<string> send_message;
    send_message.push_back("LOGIN");
    send_message.push_back(username);
    send_message.push_back(password);

    // client.SendMessage(SendHashMessage(send_message));
    SendMessage(send_message);
    string check = RecvMessage(send_message).second;
    cout << "check: " << check << endl;

    if (check == "#login_fail")
    {
        QMessageBox msgBox;
        msgBox.setText("Wrong username or password or account does not exists");
        msgBox.exec();
        ui->username_input_login->setText("");
        ui->password_input_login->setText("");
        return;
    }
    else if (check == "#login_success")
    {

        client.setname_str(username);
        ui->username_button->setText(QString::fromStdString(username));

        ui->stackedWidget->setCurrentWidget(ui->ChooseRoom);
        RefreshChooseRoomWidget();
    }
}

// ApplicationMenu Widget
void ClientQT::on_logout_ApplicationMenu_clicked()
{
    vector<string> send_message;
    send_message.push_back("LOGOUT");
    client.SendMessage(SendHashMessage(send_message));
    usleep(10000);
    string check = client.RecvMessage().second;
    cout << "check Logout: " << check << endl;
    if (checkExit(check) == 0)
    {
        return;
    }
    ui->stackedWidget->setCurrentWidget(ui->authentication);
}
void ClientQT::on_delete_account_ApplicationMenu_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->DeleteAccount);
}
vector<pair<string, string>> ClientQT::ConverListRoomsRecvToListRooms(string list_rooms_rev)
{
    vector<vector<string>> room =
        client.SplitStringRoom(list_rooms_rev);
    string room_name;
    vector<string> users;
    vector<pair<string, string>> result;
    for (int i = 0; i < room.size() - 1; i++)
    {
        room_name = room[i][1];
        if (room_name.find(seperator3) != string::npos)
        {
            users = client.Split(room_name, seperator3);

            if (users[0] == string(client.get_name_str()))
            {
                room_name = users[1];
            }
            else
            {
                room_name = users[0];
            }
        }
        result.push_back({room[i][0], room_name});
    }
    return result;
}
int ClientQT::RefreshChooseRoomWidget()
{

    cout << "VO REFRESH \n";
    ui->room_name->setVisible(false);
    ui->room_setting_button->setVisible(false);
    ui->send_message_button->setVisible(false);
    ui->input_chat->setVisible(false);
    ui->list_messages_listWidget->setVisible(false);

    vector<string> message;
    message.push_back("GET_LIST_ROOMS");
    // client.SendMessage(SendHashMessage(message));
    // usleep(10000);
    // string list_rooms_rev = client.RecvMessage().second;
    SendMessage(message);
    string list_rooms_rev = RecvMessage(message).second;
    cout << "list_rooms_rev: " << list_rooms_rev << endl;
    if (checkExit(list_rooms_rev) == 0)
    {
        return -1;
    }
    // // usleep(10000);
    // // client.SendMessage("#exit_choose_room_id");
    // // usleep(10000);
    // // client.SendMessage("#exit_choose_room");
    auto list_rooms = ConverListRoomsRecvToListRooms(list_rooms_rev);
    list_rooms_map.clear();
    current_room_id = "";
//    ui->list_rooms_listWidget->setViewMode(QListView::IconMode);
    ui->list_rooms_listWidget->clear();
    for (auto x : list_rooms)
    {

        list_rooms_map.insert({x.second, x.first});
        QListWidgetItem *item = new QListWidgetItem();
        item->setText(QString::fromStdString(x.second));
        item->setSizeHint(QSize(item->sizeHint().width(), 30));
        QFont size;
        size.setPointSize(24);
        QIcon *icon = new QIcon(":/image/face_6_FILL0_wght400_GRAD0_opsz48.png");
        item->setIcon(*icon);

        item->setFont(size);


        ui->list_rooms_listWidget->addItem(item);
    }
    ui->list_messages_listWidget->scrollToBottom();
}
void ClientQT::on_back_ApplicationMenu_clicked()
{

    ui->stackedWidget->setCurrentWidget(ui->ChooseRoom);
    RefreshChooseRoomWidget();
}
void ClientQT::on_change_password_ApplicationMenu_clicked()
{
    // client.SendMessage("#F2");
    ui->stackedWidget->setCurrentWidget(ui->ChangePassword);
    ui->old_password_input_ChangePassword->setText("");
    ui->new_password_input_ChangePassword->setText("");
    ui->retype_new_password_input_ChangePassword->setText("");
}
// Delete Account
void ClientQT::on_no_button_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->ApplicationMenu);
}
int ClientQT::checkExit(string check)
{
    QMessageBox msgBox;
    if (check == "#exit")
    {
        msgBox.setText("Your account has been deleted or your password has been changed in another session ");
     
        msgBox.exec();

        ui->stackedWidget->setCurrentWidget(ui->authentication);
        exitRecvThread();
        return 0;
    }
    return -1;
}
void ClientQT::on_yes_button_clicked()
{
    // client.SendMessage("#F3");
    string user_name = client.get_name_str();
    vector<string> message;
    message.push_back("DELETE_ACCOUNT");
    message.push_back(user_name);
    // client.SendMessage(SendHashMessage(message));
    // string delete_res = client.RecvMessage().second;
    SendMessage(message);
    usleep(10000);
    string delete_res = RecvMessage(message).second;

    if (checkExit(delete_res) == 0)
    {
        return;
    };
    if (delete_res == "#delete_success")
    {
        QMessageBox msgBox;
        msgBox.setText("Delete success. Enter to continue :D");
        msgBox.exec();
    }
    else if (delete_res == "#delete_fail")
    {
        QMessageBox msgBox;
        msgBox.setText("Delete fail. Enter to continue D:");
        msgBox.exec();
    }
    ui->stackedWidget->setCurrentWidget(ui->authentication);
}

void ClientQT::on_change_button_ChangePassword_clicked()
{
    QString empty_warning = "Password can't be empty!";
    QString retype_match_warning = "Retype password isn't match!";
    QString retype_old_warning = "New password can't be the same as old password!";
    QMessageBox msgBox;
    string old_password = ui->old_password_input_ChangePassword->text().toStdString();
    if (old_password.size() == 0)
    {
        msgBox.setText(empty_warning);
        msgBox.exec();
        return;
    }
    string new_password = ui->new_password_input_ChangePassword->text().toStdString();
    if (new_password.size() == 0)
    {
        msgBox.setText(empty_warning);
        msgBox.exec();
        return;
    }
    string retype_new_password = ui->retype_new_password_input_ChangePassword->text().toStdString();
    if (retype_new_password.size() == 0)
    {
        msgBox.setText(empty_warning);
        msgBox.exec();
        return;
    }
    if (new_password != retype_new_password)
    {
        msgBox.setText(retype_match_warning);
        ui->old_password_input_ChangePassword->setText(QString::fromStdString(old_password));
        ui->new_password_input_ChangePassword->setText("");
        ui->retype_new_password_input_ChangePassword->setText("");
        msgBox.exec();
        return;
    }
    else if (old_password == retype_new_password)
    {
        msgBox.setText(retype_old_warning);
        ui->old_password_input_ChangePassword->setText("");
        ui->new_password_input_ChangePassword->setText("");
        ui->retype_new_password_input_ChangePassword->setText("");
        msgBox.exec();
        return;
    }
    // client.SendMessage(old_password);
    // usleep(10000);
    // client.SendMessage(new_password);
    vector<string> send_message;
    send_message.push_back("CHANGE_PASSWORD");
    send_message.push_back(old_password);
    send_message.push_back(new_password);

    // client.SendMessage(SendHashMessage(send_message));
    // string check = client.RecvMessage().second;
    SendMessage(send_message);
    auto check = RecvMessage(send_message).second;

    // Co the co loi, chi moi dang chay tren local
    cout << "Message check: " << check << endl;
    if (check == "#exit")
    {
        msgBox.setText("Your account has been deleted or your password has been changed in another session ");
        ui->old_password_input_ChangePassword->setText("");
        ui->new_password_input_ChangePassword->setText("");
        ui->retype_new_password_input_ChangePassword->setText("");
        msgBox.exec();

        ui->stackedWidget->setCurrentWidget(ui->authentication);
        return;
    }
    if (check == "#wrong_change_info")
    {
        msgBox.setText("Wrong old password");
        ui->old_password_input_ChangePassword->setText("");
        ui->new_password_input_ChangePassword->setText("");
        ui->retype_new_password_input_ChangePassword->setText("");
        msgBox.exec();
        return;
    }
    else if (check == "#change_fail")
    {
        msgBox.setText("Change password failed");
        ui->old_password_input_ChangePassword->setText("");
        ui->new_password_input_ChangePassword->setText("");
        ui->retype_new_password_input_ChangePassword->setText("");
        msgBox.exec();
        // client.SendMessage("#exit_chatcsl");
        ui->stackedWidget->setCurrentWidget(ui->authentication);
        return;
    }
    msgBox.setText("Change Password success");
    msgBox.exec();
    // client.SendMessage("#exit_chatcsl");
    ui->stackedWidget->setCurrentWidget(ui->authentication);
}

void ClientQT::on_back_button_ChangePassword_clicked()
{
    // client.SendMessage("#exit_change");
    ui->stackedWidget->setCurrentWidget(ui->ApplicationMenu);
}

int ClientQT::exitRecvThread()
{
    // recvMessage->Stop = true;
    // recvMessage->quit();
    if (recvMessage != NULL)
    {
        cout << "Thoat luong\n";    
        // recvMessage->wait();
        if (recvMessage->isRunning())
        {
            cout << "De xuat Thoat Luong\n";

            recvMessage->requestInterruption();
            vector<string> message;

            recvMessage->quit();
            // recvMessage->wait();

            recvMessage->exit();
            message.push_back("EXIT_THREAD");
            // // client.SendMessage(SendHashMessage(message));
            SendMessage(message);
            usleep(10000);
            // recvMessage = NULL;
            // return 0;

            return 0;
        }
    //     // recvMessage->quit();
    //     // recvMessage->wait();
        
    } else return -1;

}

// Choose Room
void ClientQT::on_username_button_clicked()
{

    exitRecvThread();
    vector<string> message;
    message.push_back("BACK");
    // client.SendMessage(SendHashMessage(message));
    SendMessage(message);
    ui->stackedWidget->setCurrentWidget(ui->ApplicationMenu);

    
}
void ClientQT::on_room_setting_button_clicked()
{
    exitRecvThread();
    cout << "Choose Room Setting \n";
    string room_name = ui->room_name->text().toStdString();
    string room_id = list_rooms_map.find(room_name)->second;
    vector<string> message;
    message.push_back("ROOM_SETTING");
    message.push_back(room_id);
    // client.SendMessage(SendHashMessage(message));
    // usleep(10000);
    // auto check =client.RecvMessage().second;
    SendMessage(message);
    usleep(10000);
    auto check = RecvMessage(message).second;
    cout << "Message check: " << check << endl;
    if (check == "#exit")
    {   
        QMessageBox msgBox;
        msgBox.setText("Your account has been deleted or your password has been changed in another session ");
        msgBox.exec();
        ui->stackedWidget->setCurrentWidget(ui->authentication);
        return;
    }
    else if (check== "#admin") {
        ui->kick_user_RoomSetting->setVisible(true);
        ui->modify_room_name_RoomSetting->setVisible(true);

    } else if (check == "#member") {
         ui->kick_user_RoomSetting->setVisible(false);
         ui->modify_room_name_RoomSetting->setVisible(false);

    } else if (check == "#exit_kick") {
        QMessageBox msgBox;
        msgBox.setText("Your account has been kick by Admin ");
        msgBox.exec();
        RefreshChooseRoomWidget();
        ui->stackedWidget->setCurrentWidget(ui->ChooseRoom);
        return;
    }
     ui->stackedWidget->setCurrentWidget(ui->RoomSetting);



}
vector<string> ClientQT::ConvertOldMessage(string old_msg)
{
}

void ClientQT::on_send_message_button_clicked()
{

    string input_chat = ui->input_chat->text().toStdString();
    if (input_chat.size() == 0)
    {
        QMessageBox msgBox;
        msgBox.setText("Please type something :((");
        msgBox.exec();
        return;
    }
    else
    {
        QListWidgetItem *item = new QListWidgetItem();
        item->setText(QString::fromStdString(client.get_name_str()) + ": " + QString::fromStdString(input_chat));
        item->setSizeHint(QSize(item->sizeHint().width(), 30));
        QFont size;
        size.setPointSize(20);
        item->setFont(size);
        ui->list_messages_listWidget->addItem(item);
        ui->input_chat->setText("");
        vector<string> message;
        string room_name = ui->room_name->text().toStdString();
        string room_id = list_rooms_map.find(room_name)->second;
        cout << "Start Send Message: " << input_chat << endl;

        cout << "room_name: " << room_name << ", room_id: " << room_id << endl;
        message.push_back("CHAT");
        message.push_back(room_id);
        message.push_back(input_chat);
        // client.SendMessage(SendHashMessage(message));
        // this->message = message;
        SendMessage(message);
        
    }
}
int ClientQT::OnNewMessage(QString message)
{
    
    if (checkExit(message.toStdString()) == 0)
    {
        return -1;
    }
    if (message.toStdString() == "#exit_kick") {
        QMessageBox msgBox;
        msgBox.setText("Your account has been kick by Admin ");
        msgBox.exec();
        exitRecvThread();
        RefreshChooseRoomWidget();
        ui->stackedWidget->setCurrentWidget(ui->ChooseRoom);
        return -1;
    }
    
    QListWidgetItem *item = new QListWidgetItem();
    // item->setText(QString::fromStdString(message));
    item->setText(message);
    
    item->setSizeHint(QSize(item->sizeHint().width(), 30));
    QFont size;
    size.setPointSize(20);
    item->setFont(size);
    ui->list_messages_listWidget->addItem(item);
    ui->list_messages_listWidget->scrollToItem(item);
}
void ClientQT::on_list_rooms_listWidget_itemClicked(QListWidgetItem *item)
{

    // if (exitRecvThread()!=0 ) return;
    string room_name = item->data(Qt::DisplayRole).toString().toStdString();
    string room_id = list_rooms_map.find(room_name)->second;
    if (current_room_id !="" && room_id == current_room_id && list_rooms_map.size() > 1) {
        cout << "the same room id\n";
        return;
    }
    current_room_id = room_id;
    exitRecvThread();
    
    cout << "\nroom_name: " << room_name << " ---  room_id: " << room_id << endl;
    ui->room_name->setText(QString::fromStdString(room_name));
    ui->room_name->setVisible(true);
    ui->room_setting_button->setVisible(true);
    ui->send_message_button->setVisible(true);
    ui->input_chat->setVisible(true);
    ui->list_messages_listWidget->setVisible(true);
    ui->list_messages_listWidget->clear();
    vector<string> send_message;
    send_message.push_back("OLD_MESSAGES");
    send_message.push_back(room_id);

    // client.SendMessage(SendHashMessage(send_message));
    // usleep(100000);
    // string check_old_messages = client.RecvMessage().second;
    SendMessage(send_message);
    usleep(100000);
    string check_old_messages = RecvMessage(send_message).second;

    cout << "OLD MESSAGE: " << check_old_messages << " \n";

    if (checkExit(check_old_messages) == 0)
    {
        return;
    }
    auto old_messages = client.SplitString(check_old_messages, hash);

    for (auto x : old_messages)
    {
        if (x.size() == 0)
            continue;
        cout << x << endl;
        QListWidgetItem *item = new QListWidgetItem();
        item->setText(QString::fromStdString(x));
        item->setSizeHint(QSize(item->sizeHint().width(), 30));
        QFont size;
        size.setPointSize(20);
        item->setFont(size);
        ui->list_messages_listWidget->addItem(item);
    }
    
    recvMessage = new RecvThread(this, this);
    connect(recvMessage, SIGNAL(NewMessage(QString)), this, SLOT(OnNewMessage(QString)));
    // connect(recvMessage, &RecvThread::finished, recvMessage, &QObject::deleteLater);
    recvMessage->start();


    // https://stackoverflow.com/questions/32264526/how-to-get-the-text-of-selected-item-from-qlistview-in-qt?noredirect=1&lq=1
}
void ClientQT::on_create_new_chat_room_button_clicked()
{
    // if (exitRecvThread()!=0) return;
    exitRecvThread();
    vector<string> message;
    message.push_back("GET_LIST_USERS");
    // client.SendMessage(SendHashMessage(message));
    // usleep(10000);
    // string list_users_rev = client.RecvMessage().second;
    SendMessage(message);
    usleep(10000);
    string list_users_rev = RecvMessage(message).second;
    cout << "list_users_rev: " << list_users_rev << endl;
    if (checkExit(list_users_rev) == 0)
    {
        return;
    }

    vector<string> list_users = client.Split(list_users_rev, seperator1);

    ui->stackedWidget->setCurrentWidget(ui->CreateRoom);
    ui->list_users_are_added_CreateRoom->setText("");
    ui->enter_room_name_CreateRoom->setText("");
    // ui->list_users_CreateRoom->setModel(model_list_users);
    ui->list_users_CreateRoom->clear();
    for (auto user : list_users)
    {
        if (user.size() == 0)
            break;
        // cout << "user: " << user << endl;
        QListWidgetItem *item = new QListWidgetItem();
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
        // item->setData(Qt::Unchecked,Qt::CheckStateRole);
        item->setText(QString::fromStdString(user));
        item->setSizeHint(QSize(item->sizeHint().width(), 30));
        QFont size;
        size.setPointSize(20);
        item->setFont(size);
        item->setTextColor(Qt::blue);
        ui->list_users_CreateRoom->addItem(item);
    }
}
// Create Rooom
void ClientQT::on_cancel_CreateRoom_clicked()
{
    RefreshChooseRoomWidget();
    ui->stackedWidget->setCurrentWidget(ui->ChooseRoom);
}

vector<string> ClientQT::SplitString(string str, string del)
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
void ClientQT::on_confirm_CreateRoom_clicked()
{
    string list_users_are_added = ui->list_users_are_added_CreateRoom->text().toStdString();

    if (list_users_are_added.size() == 0)
    {
        QMessageBox msgBox;
        msgBox.setText("Please, Choose one or more users for chatting ^_^");
        msgBox.exec();
        return;
    }
    auto list_users_are_splitted = SplitString(list_users_are_added, ", ");
    cout << list_users_are_splitted.size() << endl;
    string room_name = ui->enter_room_name_CreateRoom->text().toStdString();

    string member_str = "";
    if (room_name.size() == 0)
    {
        if (list_users_are_splitted.size() == 1)
        {

            member_str = list_users_are_splitted[0];
            if (list_rooms_map.find(member_str) != list_rooms_map.end())
            {
                QMessageBox msgBox;
                msgBox.setText("Chat Room with this user is existed ^_^");
                msgBox.exec();
                return;
            }
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setText("Please, enter room name  ^_^");
            msgBox.exec();
            return;
        }
    }
    else
    {
        // if (list_rooms_map.find(room_name) != list_rooms_map.end())
        // {
        //     QMessageBox msgBox;
        //     msgBox.setText("Room name is existed ^_^");
        //     msgBox.exec();
        //     return;
        // }
        for (auto user : list_users_are_splitted)
        {
            member_str += user + seperator1;
        }
        member_str.pop_back();

        member_str += seperator2 + room_name;
    }
    cout << "member_str: " << member_str << endl;
    vector<string> message;
    message.push_back("CREATE_ROOM");
    message.push_back(member_str);
    // client.SendMessage(SendHashMessage(message));
    SendMessage(message);
    usleep(10000);
    auto check = RecvMessage(message).second;

    cout << "Message check: " << check << endl;
    if (check == "#exit")
    {   
        QMessageBox msgBox;
        msgBox.setText("Your account has been deleted or your password has been changed in another session ");
        msgBox.exec();
        ui->stackedWidget->setCurrentWidget(ui->authentication);
        return;
    } else if (check == "#room_create_success") {
        QMessageBox msgBox;
        msgBox.setText("Create room success");
        msgBox.exec();
    } else if (check == "#room_create_fail") {
        QMessageBox msgBox;
        msgBox.setText("Create room fail");
        msgBox.exec();
    }

    ui->stackedWidget->setCurrentWidget(ui->ChooseRoom);

    RefreshChooseRoomWidget();
}

void ClientQT::on_list_users_CreateRoom_itemClicked(QListWidgetItem *item)
{
    // string user = item->data(Qt::DisplayRole).toString().toStdString();
    bool user_checked = item->data(Qt::CheckStateRole).toBool();

    item->setCheckState(user_checked == 0 ? Qt::Checked : Qt::Unchecked);
}
void ClientQT::on_list_users_CreateRoom_itemChanged(QListWidgetItem *item)
{
    string user = item->data(Qt::DisplayRole).toString().toStdString();
    bool user_checked = item->data(Qt::CheckStateRole).toBool();

    string list_users_are_added = ui->list_users_are_added_CreateRoom->text().toStdString();

    if (user_checked == true)
    {
        if (list_users_are_added.size() == 0)
        {
            list_users_are_added += user;
        }
        else
        {
            if (list_users_are_added.find(user) == string::npos)
            {
                list_users_are_added += ", " + user;
            }
        }
    }
    else
    {

        if (list_users_are_added.size() != 0)
        {
            int index = list_users_are_added.find(user);
            if (index != string::npos)
            {
                if (index == 0)
                {
                    list_users_are_added.erase(index, user.size() + 2);
                }
                else
                {
                    list_users_are_added.erase(index - 2, user.size() + 2);
                }
            }
        }
    }
    // if (ui->list_users_CreateRoom->size())
    string room_name = ui->enter_room_name_CreateRoom->text().toStdString();
    int size_of_the_checked_items_listed = 0;
    for (int i = 0; i < ui->list_users_CreateRoom->count(); i++)
    {
        if (ui->list_users_CreateRoom->item(i)->checkState() == Qt::Checked)
        {
            size_of_the_checked_items_listed++;
        }
    }
    cout << "size_of_the_checked_items_listed: " << size_of_the_checked_items_listed << endl;
    if (size_of_the_checked_items_listed == 1)
    {
        if (room_name.size() > 0)
        {
            cout << "set disable\n";
            ui->confirm_CreateRoom->setEnabled(false);
            ui->confirm_CreateRoom->repaint();
        }
        else
        {
            ui->confirm_CreateRoom->setEnabled(true);
        }
    }
    else
    {
        ui->confirm_CreateRoom->setEnabled(true);
    }

    ui->list_users_are_added_CreateRoom->setText(QString::fromStdString(list_users_are_added));
}
// Room Setting
void ClientQT::on_cancel_RoomSetting_clicked() {
    RefreshChooseRoomWidget();
    ui->stackedWidget->setCurrentWidget(ui->ChooseRoom);
}
void ClientQT::on_add_user_RoomSetting_clicked() {
    string room_name = ui->room_name->text().toStdString();
    string room_id = list_rooms_map.find(room_name)->second;
    vector<string > message;
    message.push_back("GET_LIST_USERS_OUT_THIS_ROOM");
    message.push_back(room_id);
    // client.SendMessage(SendHashMessage(message));
    // usleep(10000);

    // auto check = client.RecvMessage().second;
    SendMessage(message);
    usleep(10000);
    auto check = RecvMessage(message).second;
    cout << "Message check: " << check << endl;
    if (check == "#exit")
    {   
        QMessageBox msgBox;
        msgBox.setText("Your account has been deleted or your password has been changed in another session ");
        msgBox.exec();
        ui->stackedWidget->setCurrentWidget(ui->authentication);
        return;
    } else if (check == "#exit_kick") {
        QMessageBox msgBox;
        msgBox.setText("Your account has been kick by Admin ");
        msgBox.exec();
        RefreshChooseRoomWidget();
        ui->stackedWidget->setCurrentWidget(ui->ChooseRoom);
        return;
    } else if (check == "#no_user") {
        QMessageBox msgBox;
        msgBox.setText("Don't have users to add");
        msgBox.exec();
        RefreshChooseRoomWidget();
        ui->stackedWidget->setCurrentWidget(ui->ChooseRoom);
        return;
    } 
    vector<string> list_users = client.Split(check, seperator1);
    ui->list_users_are_added_AddUser->setText("");
    ui->stackedWidget->setCurrentWidget(ui->AddUser);
    ui->list_users_AddUser->clear();
    for (auto user: list_users) {
        if (user.size() == 0)
            break;
        // cout << "user: " << user << endl;
        QListWidgetItem *item = new QListWidgetItem();
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
        // item->setData(Qt::Unchecked,Qt::CheckStateRole);
        item->setText(QString::fromStdString(user));
        item->setSizeHint(QSize(item->sizeHint().width(), 30));
        QFont size;
        size.setPointSize(20);
        item->setFont(size);
        item->setTextColor(Qt::blue);
        // item->setForeground(Qt::black);
        ui->list_users_AddUser->addItem(item);
    }

}
void ClientQT::on_kick_user_RoomSetting_clicked() {
    string room_name = ui->room_name->text().toStdString();
    string room_id = list_rooms_map.find(room_name)->second;
    vector<string> message;
    message.push_back("GET_LIST_USERS_IN_THIS_ROOM");
    message.push_back(room_id);
    // client.SendMessage(SendHashMessage(message));
    // usleep(10000);
    // auto check = client.RecvMessage().second;
    SendMessage(message);
    usleep(10000);
    auto check = RecvMessage(message).second;

    cout << "Message check: " << check << endl;
    if (check == "#exit")
    {   
        QMessageBox msgBox;
        msgBox.setText("Your account has been deleted or your password has been changed in another session ");
        msgBox.exec();
        ui->stackedWidget->setCurrentWidget(ui->authentication);
        return;
    } else if (check == "#exit_kick") {
        QMessageBox msgBox;
        msgBox.setText("Your account has been kick by Admin ");
        msgBox.exec();
        RefreshChooseRoomWidget();
        ui->stackedWidget->setCurrentWidget(ui->ChooseRoom);
        return;
    } else if (check == "#no_user") {
        QMessageBox msgBox;
        msgBox.setText("Don't have users to kick");
        msgBox.exec();
        RefreshChooseRoomWidget();
        ui->stackedWidget->setCurrentWidget(ui->ChooseRoom);
        return;
    } 
    vector<string> list_users = client.Split(check, seperator1);
    ui->list_users_are_added_KickUser->setText("");
    ui->stackedWidget->setCurrentWidget(ui->AddUser);
    ui->list_users_KickUser->clear();
    for (auto user: list_users) {
        if (user.size() == 0)
            break;
        // cout << "user: " << user << endl;
        QListWidgetItem *item = new QListWidgetItem();
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
        // item->setData(Qt::Unchecked,Qt::CheckStateRole);
        item->setText(QString::fromStdString(user));
        item->setSizeHint(QSize(item->sizeHint().width(), 30));
        QFont size;
        size.setPointSize(20);
        item->setFont(size);
        item->setTextColor(Qt::blue);
        // item->setForeground(Qt::black);
        ui->list_users_KickUser->addItem(item);
    }
    ui->stackedWidget->setCurrentWidget(ui->KickUser);

}
void ClientQT::on_modify_room_name_RoomSetting_clicked() {
    
    ui->enter_new_room_name_ChangeRoomName->setText(ui->room_name->text());
    ui->stackedWidget->setCurrentWidget(ui->ChangeRoomName);

}
// Add User in Room Setting
void ClientQT::on_cancel_AddUser_clicked() {
    RefreshChooseRoomWidget();
    ui->stackedWidget->setCurrentWidget(ui->ChooseRoom);
}
void ClientQT::on_list_users_AddUser_itemClicked(QListWidgetItem *item) {
    bool user_checked = item->data(Qt::CheckStateRole).toBool();

    item->setCheckState(user_checked == 0 ? Qt::Checked : Qt::Unchecked);
}
void ClientQT::on_list_users_AddUser_itemChanged(QListWidgetItem *item) {
    string user = item->data(Qt::DisplayRole).toString().toStdString();
    bool user_checked = item->data(Qt::CheckStateRole).toBool();

    string list_users_are_added_AddUser = ui->list_users_are_added_AddUser->text().toStdString();

    if (user_checked == true)
    {
        if (list_users_are_added_AddUser.size() == 0)
        {
            list_users_are_added_AddUser += user;
        }
        else
        {
            if (list_users_are_added_AddUser.find(user) == string::npos)
            {
                list_users_are_added_AddUser += ", " + user;
            }
        }
    }
    else
    {

        if (list_users_are_added_AddUser.size() != 0)
        {
            int index = list_users_are_added_AddUser.find(user);
            if (index != string::npos)
            {
                if (index == 0)
                {
                    list_users_are_added_AddUser.erase(index, user.size() + 2);
                }
                else
                {
                    list_users_are_added_AddUser.erase(index - 2, user.size() + 2);
                }
            }
        }
    }
    ui->list_users_are_added_AddUser->setText(QString::fromStdString(list_users_are_added_AddUser));
}
void ClientQT::on_confirm_AddUser_clicked() {
    string list_users_are_added = ui->list_users_are_added_AddUser->text().toStdString();
     if (list_users_are_added.size() == 0)
    {
        QMessageBox msgBox;
        msgBox.setText("Please, Choose one or more users for adding ^_^");
        msgBox.exec();
        return;
    }
    auto list_users_are_splitted = SplitString(list_users_are_added, ", ");
    cout << list_users_are_splitted.size() << endl;
    string member_str="";
    for (auto user: list_users_are_splitted) {
        member_str += user + seperator1;
    }
    member_str.pop_back();
    cout << "member_str: " << member_str << endl;
    vector<string> message;
    message.push_back("ADD_USER");
    string room_name = ui->room_name->text().toStdString();
    string room_id = list_rooms_map.find(room_name)->second;
    message.push_back(room_id);
    message.push_back(member_str);
    // client.SendMessage(SendHashMessage(message));
    // usleep(1000);
    // auto check = client.RecvMessage().second;
    SendMessage(message);
    usleep(10000);
    auto check = RecvMessage(message).second;
    cout << "Message check: " << check << endl;
    if (check == "#exit")
    {   
        QMessageBox msgBox;
        msgBox.setText("Your account has been deleted or your password has been changed in another session ");
        msgBox.exec();
        ui->stackedWidget->setCurrentWidget(ui->authentication);
        return;
    } else if (check == "#exit_kick") {
        QMessageBox msgBox;
        msgBox.setText("Your account has been kick by Admin ");
        msgBox.exec();
        RefreshChooseRoomWidget();
        ui->stackedWidget->setCurrentWidget(ui->ChooseRoom);
        return;
    } else if (check == "#add_user_success") {
        QMessageBox msgBox;
        msgBox.setText("Users are added successfully");
        msgBox.exec();
        RefreshChooseRoomWidget();
        ui->stackedWidget->setCurrentWidget(ui->ChooseRoom);
        return;
    } else {
        QMessageBox msgBox;
        msgBox.setText("Unexpected error occurred");
        msgBox.exec();
        RefreshChooseRoomWidget();
        ui->stackedWidget->setCurrentWidget(ui->ChooseRoom);
    }
   
    
}
// Kick User in Room Setting

void ClientQT::on_cancel_KickUser_clicked() {
    RefreshChooseRoomWidget();
    ui->stackedWidget->setCurrentWidget(ui->ChooseRoom);
}
void ClientQT::on_list_users_KickUser_itemClicked(QListWidgetItem *item) {
    bool user_checked = item->data(Qt::CheckStateRole).toBool();

    item->setCheckState(user_checked == 0 ? Qt::Checked : Qt::Unchecked);
}
void ClientQT::on_list_users_KickUser_itemChanged(QListWidgetItem *item) {
    string user = item->data(Qt::DisplayRole).toString().toStdString();
    bool user_checked = item->data(Qt::CheckStateRole).toBool();

    string list_users_are_added_KickUser = ui->list_users_are_added_KickUser->text().toStdString();

    if (user_checked == true)
    {
        if (list_users_are_added_KickUser.size() == 0)
        {
            list_users_are_added_KickUser += user;
        }
        else
        {
            if (list_users_are_added_KickUser.find(user) == string::npos)
            {
                list_users_are_added_KickUser += ", " + user;
            }
        }
    }
    else
    {

        if (list_users_are_added_KickUser.size() != 0)
        {
            int index = list_users_are_added_KickUser.find(user);
            if (index != string::npos)
            {
                if (index == 0)
                {
                    list_users_are_added_KickUser.erase(index, user.size() + 2);
                }
                else
                {
                    list_users_are_added_KickUser.erase(index - 2, user.size() + 2);
                }
            }
        }
    }
    ui->list_users_are_added_KickUser->setText(QString::fromStdString(list_users_are_added_KickUser));
}
void ClientQT::on_confirm_KickUser_clicked() {
    string list_users_are_added = ui->list_users_are_added_KickUser->text().toStdString();
     if (list_users_are_added.size() == 0)
    {
        QMessageBox msgBox;
        msgBox.setText("Please, Choose one or more users for kicking ^_^");
        msgBox.exec();
        return;
    }
    auto list_users_are_splitted = SplitString(list_users_are_added, ", ");
    cout << list_users_are_splitted.size() << endl;
    string member_str="";
    for (auto user: list_users_are_splitted) {
        member_str += user + seperator1;
    }
    member_str.pop_back();
    cout << "member_str: " << member_str << endl;
    vector<string> message;
    message.push_back("KICK_USER");
    string room_name = ui->room_name->text().toStdString();
    string room_id = list_rooms_map.find(room_name)->second;
    message.push_back(room_id);
    message.push_back(member_str);
    // client.SendMessage(SendHashMessage(message));
    // usleep(1000);
    // auto check = client.RecvMessage().second;
    SendMessage(message);
    usleep(10000);
    auto check = RecvMessage(message).second;
    cout << "Message check: " << check << endl;
    if (check == "#exit")
    {   
        QMessageBox msgBox;
        msgBox.setText("Your account has been deleted or your password has been changed in another session ");
        msgBox.exec();
        ui->stackedWidget->setCurrentWidget(ui->authentication);
        return;
    } else if (check == "#exit_kick") {
        QMessageBox msgBox;
        msgBox.setText("Your account has been kick by Admin ");
        msgBox.exec();
        RefreshChooseRoomWidget();
        ui->stackedWidget->setCurrentWidget(ui->ChooseRoom);
        return;
    } else if (check == "#kick_user_success") {
        QMessageBox msgBox;
        msgBox.setText("Users are kicked successfully");
        msgBox.exec();
        RefreshChooseRoomWidget();
        ui->stackedWidget->setCurrentWidget(ui->ChooseRoom);
        return;
    } else {
        QMessageBox msgBox;
        msgBox.setText("Unexpected error occurred");
        msgBox.exec();
        RefreshChooseRoomWidget();
        ui->stackedWidget->setCurrentWidget(ui->ChooseRoom);
    }
}
// Modify room name
void ClientQT::on_cancel_ChangeRoomName_clicked() {
    RefreshChooseRoomWidget();
    ui->stackedWidget->setCurrentWidget(ui->ChooseRoom);
}
void ClientQT::on_confirm_ChangeRoomName_clicked() {
    string old_room_name = ui->room_name->text().toStdString();
    string room_id = list_rooms_map.find(old_room_name)->second;
    string new_room_name = ui->enter_new_room_name_ChangeRoomName->text().toStdString();
    if (new_room_name.size() == 0) {
        QMessageBox msgBox;
        msgBox.setText("Room Name can't be empty");
        msgBox.exec();
        return;
    }
    if (old_room_name == new_room_name) {
        RefreshChooseRoomWidget();
        ui->stackedWidget->setCurrentWidget(ui->ChooseRoom);
    } else {
        vector<string> message;
        message.push_back("MODIFY_ROOM_NAME");
        message.push_back(room_id);
        message.push_back(new_room_name);
        // client.SendMessage(SendHashMessage(message));
        // usleep(10000);
        // auto check = client.RecvMessage().second;
        SendMessage(message);
        usleep(10000);
        auto check = RecvMessage(message).second;
        cout << "Message check: " << check << endl;
        if (check == "#exit")
        {
            QMessageBox msgBox;
            msgBox.setText("Your account has been deleted or your password has been changed in another session ");
            msgBox.exec();
            ui->stackedWidget->setCurrentWidget(ui->authentication);
            return;
        }
        else if (check == "#exit_kick")
        {
            QMessageBox msgBox;
            msgBox.setText("Your account has been kick by Admin ");
            msgBox.exec();
            RefreshChooseRoomWidget();
            ui->stackedWidget->setCurrentWidget(ui->ChooseRoom);
            return;
        }
        else if (check == "#change_room_name_success") {
            QMessageBox msgBox;
            msgBox.setText("Change roome name success");
            msgBox.exec();
            RefreshChooseRoomWidget();
            ui->stackedWidget->setCurrentWidget(ui->ChooseRoom);
            return;
        } else {
            QMessageBox msgBox;
            msgBox.setText("Change roome name fail");
            msgBox.exec();
            RefreshChooseRoomWidget();
            ui->stackedWidget->setCurrentWidget(ui->ChooseRoom);
            return;
        }
    }
}
// 
void ClientQT::closeEvent(QCloseEvent *event)
{

        exitRecvThread();
        vector<string> message;
        message.push_back("#CLOSE");
        // client.SendMessage(SendHashMessage(message));
        SendMessage(message);
       
    // }
}
int ClientQT::SendMessage(vector<string> message) {
    cout << "Start Send Message\n";
    int send_status = client.SendMessage(SendHashMessage(message));
    cout << "send_status: " << send_status << endl;

    if (send_status <=0) {
        cout << "Server Down, reconnecting\n";
        ui->stackedWidget->hide();
        ui->waiting_label->setVisible(true);

        client.CreateSocket();
        ConnectServer();
        CheckAndReconnectServer(message);
        cout << "show again\n";
        

        

    } 
    ui->waiting_label->setVisible(false);

    ui->stackedWidget->show();
    return send_status;
}
int ClientQT::ConnectServer() {
   
    return client.ConnectServer();

}
pair<int,string> ClientQT::RecvMessage(vector<string> message) {
    auto check = client.RecvMessage();
    cout << "size RecvMessage: " << check.first << endl;
    // cout << "server down nhen\n";
   

    if (check.first <=0 ) {

            cout << "Server Down, reconnecting\n";
            ui->stackedWidget->hide();

            ui->waiting_label->setVisible(true);
            client.CreateSocket();
            ConnectServer();
            CheckAndReconnectServer(message);
            usleep(10000);
            check = RecvMessage(message);

       
    }
    ui->waiting_label->setVisible(false);

    ui->stackedWidget->show();
    return check;
}
int ClientQT::CheckAndReconnectServer(vector<string> message) {

    if (message.size() == 0) {
        string username = ui->username_button->text().toStdString();
        string room_name = ui->room_name->text().toStdString();
        string room_id = list_rooms_map.find(room_name)->second;
        cout << "Send Empty message\n";
        message.push_back("RECONNECTION");
        message.push_back("EMPTY");
        message.push_back(username);
        message.push_back(room_id);
        SendMessage(message);

        return 0;
    }
   string option = message[0];
   if (option == "LOGIN") {
        string username = message[1], password = message[2];
        cout << "Resend message LOGIN*****\n";
       
        message.insert(message.begin(),"RECONNECTION");
        SendMessage(message);
        usleep(10000);
        
//        LoadLogin(username, password);
        usleep(10000);

   } else if (option == "#CLOSE") {
        message.insert(message.begin(),"RECONNECTION");
        SendMessage(message);
   } else if (option == "REGISTER") {
        string username = message[1], password = message[2];
        cout << "Resend message REGISTER*****\n";
        message.insert(message.begin(),"RECONNECTION");
        SendMessage(message);
        usleep(10000);
//        LoadRegister(username,password);

   } else if (option == "CHANGE_PASSWORD") {
        string username = client.get_name_str();
        string old_password = message[1], new_password = message[2];
        cout << "Resend message CHANGE_PASSWORD*****\n";
        
        message.insert(message.begin(),"RECONNECTION");
        message.push_back(username);

        SendMessage(message);
        usleep(10000);
//        LoadChangePassword(username, old_password, new_password);

   } else if (option == "DELETE_ACCOUNT") {
        string username = client.get_name_str();
        cout << "Resend message DELETE_ACCOUNT*****\n";
        message.insert(message.begin(),"RECONNECTION");
        message.push_back(username);
        SendMessage(message);
        usleep(10000);
        ui->stackedWidget->setCurrentWidget(ui->DeleteAccount);
   } else if (option == "BACK") {
        string username = client.get_name_str();
        cout << "Resend message BACK*****\n";
        message.insert(message.begin(),"RECONNECTION");
        message.push_back(username);
        SendMessage(message);
        usleep(10000);
        ui->stackedWidget->setCurrentWidget(ui->ApplicationMenu);
   } else if (option == "EXIT_THREAD") {
        string username = client.get_name_str();
        cout << "Resend message EXIT_THREAD*****\n";
        message.insert(message.begin(),"RECONNECTION");
        message.push_back(username);
        SendMessage(message);
        usleep(10000);
   } else if (option == "GET_LIST_ROOMS") {
        string username = client.get_name_str();
        cout << "Resend message GET_LIST_ROOMS*****\n";
        message.insert(message.begin(),"RECONNECTION");
        message.push_back(username);
        SendMessage(message);
        usleep(10000);
   } else if (option == "GET_LIST_USERS") {
        string username = client.get_name_str();
        cout << "Resend message GET_LIST_ROOMS*****\n";
        message.insert(message.begin(),"RECONNECTION");
        message.push_back(username);
        SendMessage(message);
        usleep(10000);
   } else if (option == "CREATE_ROOM") {
        string username = client.get_name_str();
        cout << "Resend message CREATE_ROOM*****\n";
        message.insert(message.begin(),"RECONNECTION");
        message.push_back(username);
        SendMessage(message);
        usleep(10000);
   } else if (option == "OLD_MESSAGES") {
        string username = client.get_name_str();
        cout << "Resend message OLD_MESSAGES*****\n";
        message.insert(message.begin(),"RECONNECTION");
        message.push_back(username);
        SendMessage(message);
        usleep(10000);
   } else if (option == "CHAT") {
        string username = client.get_name_str();
        cout << "Resend message CHAT*****\n";
        message.insert(message.begin(),"RECONNECTION");
        message.push_back(username);
        SendMessage(message);
        usleep(10000);
   } else if (option == "ROOM_SETTING") {
        string username = client.get_name_str();
        cout << "Resend message ROOM_SETTING*****\n";
        message.insert(message.begin(),"RECONNECTION");
        message.push_back(username);
        SendMessage(message);
        usleep(10000);
   } else if (option == "GET_LIST_USERS_OUT_THIS_ROOM") {
        string username = client.get_name_str();
        cout << "Resend message GET_LIST_USERS_OUT_THIS_ROOM*****\n";
        message.insert(message.begin(),"RECONNECTION");
        message.push_back(username);
        SendMessage(message);
        usleep(10000);
   } else if (option == "ADD_USER") {
        string username = client.get_name_str();
        cout << "Resend message ADD_USER*****\n";
        message.insert(message.begin(),"RECONNECTION");
        message.push_back(username);
        SendMessage(message);
        usleep(10000);
   } else if (option == "GET_LIST_USERS_IN_THIS_ROOM") {
        string username = client.get_name_str();
        cout << "Resend message GET_LIST_USERS_IN_THIS_ROOM*****\n";
        message.insert(message.begin(),"RECONNECTION");
        message.push_back(username);
        SendMessage(message);
        usleep(10000);
   } else if (option == "KICK_USER") {
        string username = client.get_name_str();
        cout << "Resend message KICK_USER*****\n";
        message.insert(message.begin(),"RECONNECTION");
        message.push_back(username);
        SendMessage(message);
        usleep(10000);
   } else if (option == "MODIFY_ROOM_NAME") {
        string username = client.get_name_str();
        cout << "Resend message MODIFY_ROOM_NAME*****\n";
        message.insert(message.begin(),"RECONNECTION");
        message.push_back(username);
        SendMessage(message);
        usleep(10000);
   }
}
int ClientQT::LoadChangePassword(string username, string old_password, string new_password) {
    ui->old_password_input_ChangePassword->setText(QString::fromStdString(old_password));
    ui->new_password_input_ChangePassword->setText(QString::fromStdString(new_password));
    ui->retype_new_password_input_ChangePassword->setText(QString::fromStdString(new_password));
    ui->stackedWidget->setCurrentWidget(ui->ChangePassword);

}
int ClientQT::LoadLogin(string username, string password) {
    ui->username_input_login->setText(QString::fromStdString(username));
    ui->password_input_login->setText(QString::fromStdString(password));
    ui->stackedWidget->setCurrentWidget(ui->Login);
}
int ClientQT::LoadRegister(string username, string password) {
    ui->username_input_Register->setText(QString::fromStdString(username));
    ui->password_input_Register->setText(QString::fromStdString(password));
    ui->retype_password_input_Register->setText(QString::fromStdString(password));
    ui->stackedWidget->setCurrentWidget(ui->Register);

}
