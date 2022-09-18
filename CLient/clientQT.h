#ifndef CLIENT_H
#define CLIENT_H
#include <QDebug>
#include <QWidget>
#include <QSplashScreen>
#include <QMessageBox>
#include <QStringListModel>
#include <QListWidget>
#include <QThread>
#include "recvthread.h"
#include <QIcon>
#include <regex>
#include <map>
#include <QCloseEvent>
#include <QKeyEvent>
#include <QPixmap>
#include <QShortcut>
#include <QScrollBar>
using std::map;
namespace Ui {
class ClientQT;

}
class Client;
class RecvThread;
class ClientQT : public QWidget
{
    Q_OBJECT

public:
    explicit ClientQT(QWidget *parent = 0);
    vector<pair<string,string>> ConverListRoomsRecvToListRooms(string list_rooms);
    vector<string> ConvertOldMessage(string old_msg);
    vector<string> SplitString(string str,string del = " ");
    string SendHashMessage(vector<string> list_messages);
    int RefreshChooseRoomWidget();
    int checkExit(string check);
    int exitRecvThread();
    int SendMessage(vector<string> message);
    pair<int,string> RecvMessage(vector<string> message);
    int CheckAndReconnectServer(vector<string> message);
    int ConnectServer();
    int LoadLogin(string username, string password);
    int LoadRegister(string username, string password);
    int LoadChangePassword(string username, string old_password, string new_password);
    vector<string > message;
    ~ClientQT();
public slots: 
    int OnNewMessage(QString);
private slots:
    
    
    // Authentication menu Widget
    void on_register_button_authentication_clicked();
    void on_exit_button_authentication_clicked();
    void on_login_button_authentication_clicked();
    // Register Widget
    void on_back_button_Register_clicked();
    void on_confirm_register_button_clicked();
    // Login Widget
    void on_back_button_login_clicked();
    void on_confirm_login_button_clicked();
    // ApplicationMenu Widget
    void on_logout_ApplicationMenu_clicked();
    void on_back_ApplicationMenu_clicked();
    void on_change_password_ApplicationMenu_clicked();
    void on_delete_account_ApplicationMenu_clicked();
    // Delete account
    void on_no_button_clicked();
    void on_yes_button_clicked();
    // Change Password
    void on_change_button_ChangePassword_clicked();
    void on_back_button_ChangePassword_clicked();
    // Choose room 
    void on_username_button_clicked();
    void on_create_new_chat_room_button_clicked();
    void on_list_rooms_listWidget_itemClicked(QListWidgetItem *item);
    void on_send_message_button_clicked();
    void on_room_setting_button_clicked();
    // Create room
    void on_cancel_CreateRoom_clicked();
    void on_confirm_CreateRoom_clicked();
    // void on_list_users_CreateRoom_clicked(const QModelIndex &index);    
    void on_list_users_CreateRoom_itemClicked(QListWidgetItem *item);
    void on_list_users_CreateRoom_itemChanged(QListWidgetItem *item);
    // Room Setting
    void on_cancel_RoomSetting_clicked();
    void on_add_user_RoomSetting_clicked();
    void on_kick_user_RoomSetting_clicked();
    void on_modify_room_name_RoomSetting_clicked();
    // Add User in Room Setting
    void on_cancel_AddUser_clicked();
    void on_list_users_AddUser_itemClicked(QListWidgetItem *item);
    void on_list_users_AddUser_itemChanged(QListWidgetItem *item);
    void on_confirm_AddUser_clicked();
    
    // Kick User in Room Setting

    void on_cancel_KickUser_clicked();
    void on_list_users_KickUser_itemClicked(QListWidgetItem *item);
    void on_list_users_KickUser_itemChanged(QListWidgetItem *item);
    void on_confirm_KickUser_clicked();
    // Modify room name
    void on_cancel_ChangeRoomName_clicked();
    void on_confirm_ChangeRoomName_clicked();
    void closeEvent (QCloseEvent *event);
//    void keyPressEvent(QKeyEvent *event);
protected:
      void keyPressEvent(QKeyEvent *event);
private:
    Ui::ClientQT *ui;
    map<string,string> list_rooms_map;
    Client client;
    RecvThread *recvMessage;
    string current_room_id;
};

#endif // CLIENT_H
