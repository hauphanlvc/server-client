/********************************************************************************
** Form generated from reading UI file 'clientQT.ui'
**
** Created by: Qt User Interface Compiler version 5.15.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENTQT_H
#define UI_CLIENTQT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClientQT
{
public:
    QStackedWidget *stackedWidget;
    QWidget *authentication;
    QPushButton *register_button_authentication;
    QPushButton *exit_button_authentication;
    QPushButton *login_button_authentication;
    QWidget *ChooseRoom;
    QLabel *label_message;
    QPushButton *create_new_chat_room_button;
    QListWidget *list_rooms_listWidget;
    QLabel *room_name;
    QPushButton *room_setting_button;
    QLineEdit *input_chat;
    QPushButton *send_message_button;
    QListWidget *list_messages_listWidget;
    QPushButton *username_button;
    QWidget *Login;
    QLabel *label_4;
    QLabel *username_login;
    QLabel *password_login;
    QPushButton *back_button_login;
    QPushButton *confirm_login_button;
    QLineEdit *username_input_login;
    QLineEdit *password_input_login;
    QWidget *ApplicationMenu;
    QPushButton *back_ApplicationMenu;
    QPushButton *change_password_ApplicationMenu;
    QPushButton *delete_account_ApplicationMenu;
    QPushButton *logout_ApplicationMenu;
    QWidget *Register;
    QLabel *label_3_Register;
    QLabel *username_Register;
    QLabel *password_Register;
    QPushButton *back_button_Register;
    QPushButton *confirm_register_button;
    QLineEdit *username_input_Register;
    QLineEdit *password_input_Register;
    QLineEdit *retype_password_input_Register;
    QLabel *password_Register_2;
    QWidget *ChangePassword;
    QLabel *label_ChangePassword;
    QLabel *label_old_password_ChangePassword;
    QLabel *label_new_password_ChangePassword;
    QLabel *label_retype_new_password_ChangePassword;
    QPushButton *change_button_ChangePassword;
    QPushButton *back_button_ChangePassword;
    QLineEdit *old_password_input_ChangePassword;
    QLineEdit *new_password_input_ChangePassword;
    QLineEdit *retype_new_password_input_ChangePassword;
    QWidget *DeleteAccount;
    QLabel *label;
    QLabel *label_2;
    QPushButton *yes_button;
    QPushButton *no_button;
    QWidget *CreateRoom;
    QLabel *label_3;
    QLineEdit *enter_room_name_CreateRoom;
    QLabel *list_users_are_added_CreateRoom;
    QLineEdit *search_user_CreateRoom;
    QListWidget *list_users_CreateRoom;
    QPushButton *confirm_CreateRoom;
    QPushButton *cancel_CreateRoom;
    QWidget *RoomSetting;
    QPushButton *add_user_RoomSetting;
    QPushButton *kick_user_RoomSetting;
    QPushButton *cancel_RoomSetting;
    QPushButton *modify_room_name_RoomSetting;
    QWidget *AddUser;
    QListWidget *list_users_AddUser;
    QPushButton *cancel_AddUser;
    QPushButton *confirm_AddUser;
    QLabel *label_5;
    QLabel *list_users_are_added_AddUser;
    QWidget *KickUser;
    QLabel *label_6;
    QPushButton *cancel_KickUser;
    QPushButton *confirm_KickUser;
    QListWidget *list_users_KickUser;
    QLabel *list_users_are_added_KickUser;
    QWidget *ChangeRoomName;
    QPushButton *confirm_ChangeRoomName;
    QPushButton *cancel_ChangeRoomName;
    QLabel *label_7;
    QLineEdit *enter_new_room_name_ChangeRoomName;
    QWidget *Reload;
    QLabel *label_8;

    void setupUi(QWidget *ClientQT)
    {
        if (ClientQT->objectName().isEmpty())
            ClientQT->setObjectName(QString::fromUtf8("ClientQT"));
        ClientQT->resize(969, 767);
        stackedWidget = new QStackedWidget(ClientQT);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(90, 30, 761, 641));
        stackedWidget->setStyleSheet(QString::fromUtf8("\n"
"background-image: url(:/image/jisoo_resize.png);\n"
"\n"
""));
        authentication = new QWidget();
        authentication->setObjectName(QString::fromUtf8("authentication"));
        authentication->setStyleSheet(QString::fromUtf8(""));
        register_button_authentication = new QPushButton(authentication);
        register_button_authentication->setObjectName(QString::fromUtf8("register_button_authentication"));
        register_button_authentication->setGeometry(QRect(10, 500, 151, 61));
        register_button_authentication->setStyleSheet(QString::fromUtf8("background-color: #4D92FF;\n"
"border-radius: 10px;\n"
"color: #FFFFFF;\n"
"\n"
""));
        exit_button_authentication = new QPushButton(authentication);
        exit_button_authentication->setObjectName(QString::fromUtf8("exit_button_authentication"));
        exit_button_authentication->setEnabled(true);
        exit_button_authentication->setGeometry(QRect(540, 510, 141, 51));
        exit_button_authentication->setAutoFillBackground(false);
        exit_button_authentication->setStyleSheet(QString::fromUtf8("background-color: rgb(77, 146, 255);\n"
"border-radius: 10px;\n"
"color: #FFFFFF;\n"
"\n"
""));
        exit_button_authentication->setCheckable(false);
        exit_button_authentication->setChecked(false);
        login_button_authentication = new QPushButton(authentication);
        login_button_authentication->setObjectName(QString::fromUtf8("login_button_authentication"));
        login_button_authentication->setGeometry(QRect(290, 500, 131, 61));
        login_button_authentication->setStyleSheet(QString::fromUtf8("background-color: #4D92FF;\n"
"border-radius: 10px;\n"
"color: #FFFFFF;\n"
"\n"
""));
        stackedWidget->addWidget(authentication);
        ChooseRoom = new QWidget();
        ChooseRoom->setObjectName(QString::fromUtf8("ChooseRoom"));
        ChooseRoom->setStyleSheet(QString::fromUtf8(""));
        label_message = new QLabel(ChooseRoom);
        label_message->setObjectName(QString::fromUtf8("label_message"));
        label_message->setGeometry(QRect(60, 20, 71, 31));
        label_message->setStyleSheet(QString::fromUtf8("\n"
"\n"
"font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"font-size: 14px;\n"
"line-height: 29px;\n"
"/* identical to box height */\n"
"\n"
"\n"
"color: #FFFFFF;"));
        create_new_chat_room_button = new QPushButton(ChooseRoom);
        create_new_chat_room_button->setObjectName(QString::fromUtf8("create_new_chat_room_button"));
        create_new_chat_room_button->setGeometry(QRect(20, 60, 101, 31));
        create_new_chat_room_button->setStyleSheet(QString::fromUtf8("\n"
"\n"
"font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"font-size: 14px;\n"
"line-height: 29px;\n"
"/* identical to box height */\n"
"\n"
"\n"
"color: #FFFFFF;"));
        list_rooms_listWidget = new QListWidget(ChooseRoom);
        list_rooms_listWidget->setObjectName(QString::fromUtf8("list_rooms_listWidget"));
        list_rooms_listWidget->setGeometry(QRect(10, 110, 111, 451));
        list_rooms_listWidget->setStyleSheet(QString::fromUtf8("\n"
"\n"
"font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"font-size: 14px;\n"
"line-height: 29px;\n"
"/* identical to box height */\n"
"\n"
"\n"
"color: #FFFFFF;"));
        room_name = new QLabel(ChooseRoom);
        room_name->setObjectName(QString::fromUtf8("room_name"));
        room_name->setGeometry(QRect(160, 30, 91, 51));
        room_name->setStyleSheet(QString::fromUtf8("\n"
"\n"
"font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"font-size: 14px;\n"
"line-height: 29px;\n"
"/* identical to box height */\n"
"\n"
"\n"
"color: #FFFFFF;"));
        room_setting_button = new QPushButton(ChooseRoom);
        room_setting_button->setObjectName(QString::fromUtf8("room_setting_button"));
        room_setting_button->setGeometry(QRect(450, 30, 121, 41));
        room_setting_button->setStyleSheet(QString::fromUtf8("\n"
"\n"
"font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"font-size: 14px;\n"
"line-height: 29px;\n"
"/* identical to box height */\n"
"\n"
"\n"
"color: #FFFFFF;"));
        input_chat = new QLineEdit(ChooseRoom);
        input_chat->setObjectName(QString::fromUtf8("input_chat"));
        input_chat->setGeometry(QRect(140, 530, 361, 31));
        input_chat->setStyleSheet(QString::fromUtf8("font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"font-size: 14px;\n"
"line-height: 29px;\n"
"/* identical to box height */\n"
"\n"
"\n"
"\n"
"\n"
"background: #24262A;\n"
"border: 1px solid #FFFFFF;\n"
"border-radius: 10px;\n"
"color: #FFFFFF;\n"
"\n"
"padding-left: 5px; padding-right: 3px;\n"
"\n"
"padding-top: 1px; padding-bottom: 1px;"));
        send_message_button = new QPushButton(ChooseRoom);
        send_message_button->setObjectName(QString::fromUtf8("send_message_button"));
        send_message_button->setGeometry(QRect(519, 532, 81, 31));
        send_message_button->setStyleSheet(QString::fromUtf8("background-color: #4D92FF;\n"
"border-radius: 10px;\n"
"\n"
"font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"font-size: 14px;\n"
"line-height: 29px;\n"
"/* identical to box height */\n"
"\n"
"\n"
"color: #FFFFFF;"));
        list_messages_listWidget = new QListWidget(ChooseRoom);
        list_messages_listWidget->setObjectName(QString::fromUtf8("list_messages_listWidget"));
        list_messages_listWidget->setGeometry(QRect(135, 111, 601, 401));
        list_messages_listWidget->setStyleSheet(QString::fromUtf8("\n"
"\n"
"font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"font-size: 14px;\n"
"line-height: 29px;\n"
"/* identical to box height */\n"
"\n"
"\n"
"color: #FFFFFF;"));
        username_button = new QPushButton(ChooseRoom);
        username_button->setObjectName(QString::fromUtf8("username_button"));
        username_button->setGeometry(QRect(0, 20, 51, 31));
        username_button->setStyleSheet(QString::fromUtf8("background-color: rgb(77, 146, 255);\n"
"border-radius: 10px;\n"
"color: #FFFFFF;\n"
"\n"
""));
        stackedWidget->addWidget(ChooseRoom);
        Login = new QWidget();
        Login->setObjectName(QString::fromUtf8("Login"));
        label_4 = new QLabel(Login);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 60, 541, 61));
        label_4->setStyleSheet(QString::fromUtf8("position: absolute;\n"
"width: 498px;\n"
"height: 58px;\n"
"left: 471px;\n"
"top: 193px;\n"
"\n"
"font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"font-size: 48px;\n"
"line-height: 58px;\n"
"/* identical to box height */\n"
"\n"
"\n"
"color: #FFFFFF;"));
        username_login = new QLabel(Login);
        username_login->setObjectName(QString::fromUtf8("username_login"));
        username_login->setGeometry(QRect(20, 160, 161, 41));
        username_login->setAutoFillBackground(false);
        username_login->setStyleSheet(QString::fromUtf8("\n"
"\n"
"font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"font-size: 24px;\n"
"line-height: 29px;\n"
"/* identical to box height */\n"
"\n"
"\n"
"color: #FFFFFF;"));
        password_login = new QLabel(Login);
        password_login->setObjectName(QString::fromUtf8("password_login"));
        password_login->setGeometry(QRect(30, 310, 161, 41));
        password_login->setAutoFillBackground(false);
        password_login->setStyleSheet(QString::fromUtf8("position: absolute;\n"
"width: 118px;\n"
"height: 29px;\n"
"left: 410px;\n"
"top: 323px;\n"
"\n"
"font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"font-size: 24px;\n"
"line-height: 29px;\n"
"/* identical to box height */\n"
"\n"
"\n"
"color: #FFFFFF;"));
        back_button_login = new QPushButton(Login);
        back_button_login->setObjectName(QString::fromUtf8("back_button_login"));
        back_button_login->setGeometry(QRect(40, 480, 101, 41));
        back_button_login->setStyleSheet(QString::fromUtf8("border-radius: 10px;\n"
"color: #4D92FF;\n"
"background-color: #FFFFFF;\n"
""));
        confirm_login_button = new QPushButton(Login);
        confirm_login_button->setObjectName(QString::fromUtf8("confirm_login_button"));
        confirm_login_button->setGeometry(QRect(380, 480, 101, 41));
        confirm_login_button->setStyleSheet(QString::fromUtf8("border-radius: 10px;\n"
"color: #FFFFFF;\n"
"background-color: #4D92FF;\n"
""));
        username_input_login = new QLineEdit(Login);
        username_input_login->setObjectName(QString::fromUtf8("username_input_login"));
        username_input_login->setGeometry(QRect(30, 220, 471, 41));
        username_input_login->setStyleSheet(QString::fromUtf8("font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"font-size: 14px;\n"
"line-height: 29px;\n"
"/* identical to box height */\n"
"\n"
"\n"
"\n"
"\n"
"background: #24262A;\n"
"border: 1px solid #FFFFFF;\n"
"border-radius: 10px;\n"
"color: #FFFFFF;\n"
"\n"
"padding-left: 5px; padding-right: 3px;\n"
"\n"
"padding-top: 1px; padding-bottom: 1px;"));
        password_input_login = new QLineEdit(Login);
        password_input_login->setObjectName(QString::fromUtf8("password_input_login"));
        password_input_login->setGeometry(QRect(30, 380, 471, 41));
        password_input_login->setStyleSheet(QString::fromUtf8("font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"font-size: 14px;\n"
"line-height: 29px;\n"
"/* identical to box height */\n"
"\n"
"\n"
"\n"
"\n"
"background: #24262A;\n"
"border: 1px solid #FFFFFF;\n"
"border-radius: 10px;\n"
"color: #FFFFFF;\n"
"\n"
"padding-left: 5px; padding-right: 3px;\n"
"\n"
"padding-top: 1px; padding-bottom: 1px;"));
        password_input_login->setEchoMode(QLineEdit::PasswordEchoOnEdit);
        stackedWidget->addWidget(Login);
        ApplicationMenu = new QWidget();
        ApplicationMenu->setObjectName(QString::fromUtf8("ApplicationMenu"));
        back_ApplicationMenu = new QPushButton(ApplicationMenu);
        back_ApplicationMenu->setObjectName(QString::fromUtf8("back_ApplicationMenu"));
        back_ApplicationMenu->setGeometry(QRect(30, 110, 241, 111));
        back_ApplicationMenu->setStyleSheet(QString::fromUtf8("background-color: #4D92FF;\n"
"border-radius: 10px;\n"
"color: #FFFFFF;\n"
"\n"
""));
        change_password_ApplicationMenu = new QPushButton(ApplicationMenu);
        change_password_ApplicationMenu->setObjectName(QString::fromUtf8("change_password_ApplicationMenu"));
        change_password_ApplicationMenu->setGeometry(QRect(310, 110, 281, 111));
        change_password_ApplicationMenu->setStyleSheet(QString::fromUtf8("background-color: #47E869;radius;\n"
"border-radius: 10px;\n"
"color: #FFFFFF;\n"
"\n"
""));
        delete_account_ApplicationMenu = new QPushButton(ApplicationMenu);
        delete_account_ApplicationMenu->setObjectName(QString::fromUtf8("delete_account_ApplicationMenu"));
        delete_account_ApplicationMenu->setGeometry(QRect(30, 280, 251, 111));
        delete_account_ApplicationMenu->setStyleSheet(QString::fromUtf8("background-color: #EF6461;\n"
"border-radius: 10px;\n"
"color: #FFFFFF;\n"
"\n"
""));
        logout_ApplicationMenu = new QPushButton(ApplicationMenu);
        logout_ApplicationMenu->setObjectName(QString::fromUtf8("logout_ApplicationMenu"));
        logout_ApplicationMenu->setGeometry(QRect(310, 280, 281, 111));
        logout_ApplicationMenu->setStyleSheet(QString::fromUtf8("background-color: #EABF67;\n"
"border-radius: 10px;\n"
"color: #FFFFFF;\n"
""));
        stackedWidget->addWidget(ApplicationMenu);
        Register = new QWidget();
        Register->setObjectName(QString::fromUtf8("Register"));
        label_3_Register = new QLabel(Register);
        label_3_Register->setObjectName(QString::fromUtf8("label_3_Register"));
        label_3_Register->setGeometry(QRect(20, 40, 541, 61));
        label_3_Register->setStyleSheet(QString::fromUtf8("position: absolute;\n"
"width: 498px;\n"
"height: 58px;\n"
"left: 471px;\n"
"top: 193px;\n"
"\n"
"font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"font-size: 48px;\n"
"line-height: 58px;\n"
"/* identical to box height */\n"
"\n"
"\n"
"color: #FFFFFF;"));
        username_Register = new QLabel(Register);
        username_Register->setObjectName(QString::fromUtf8("username_Register"));
        username_Register->setGeometry(QRect(20, 140, 161, 41));
        username_Register->setAutoFillBackground(false);
        username_Register->setStyleSheet(QString::fromUtf8("position: absolute;\n"
"width: 118px;\n"
"height: 29px;\n"
"left: 410px;\n"
"top: 323px;\n"
"\n"
"font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"font-size: 24px;\n"
"line-height: 29px;\n"
"/* identical to box height */\n"
"\n"
"\n"
"color: #FFFFFF;"));
        password_Register = new QLabel(Register);
        password_Register->setObjectName(QString::fromUtf8("password_Register"));
        password_Register->setGeometry(QRect(20, 280, 161, 41));
        password_Register->setAutoFillBackground(false);
        password_Register->setStyleSheet(QString::fromUtf8("position: absolute;\n"
"width: 118px;\n"
"height: 29px;\n"
"left: 410px;\n"
"top: 323px;\n"
"\n"
"font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"font-size: 24px;\n"
"line-height: 29px;\n"
"/* identical to box height */\n"
"\n"
"\n"
"color: #FFFFFF;"));
        back_button_Register = new QPushButton(Register);
        back_button_Register->setObjectName(QString::fromUtf8("back_button_Register"));
        back_button_Register->setGeometry(QRect(10, 530, 101, 41));
        back_button_Register->setStyleSheet(QString::fromUtf8("border-radius: 10px;\n"
"color: #4D92FF;\n"
"background-color: #FFFFFF;\n"
""));
        confirm_register_button = new QPushButton(Register);
        confirm_register_button->setObjectName(QString::fromUtf8("confirm_register_button"));
        confirm_register_button->setGeometry(QRect(370, 530, 101, 41));
        confirm_register_button->setStyleSheet(QString::fromUtf8("border-radius: 10px;\n"
"color: #FFFFFF;\n"
"background-color: #4D92FF;\n"
""));
        username_input_Register = new QLineEdit(Register);
        username_input_Register->setObjectName(QString::fromUtf8("username_input_Register"));
        username_input_Register->setGeometry(QRect(20, 210, 471, 41));
        username_input_Register->setStyleSheet(QString::fromUtf8("font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"font-size: 14px;\n"
"line-height: 29px;\n"
"/* identical to box height */\n"
"\n"
"\n"
"\n"
"\n"
"background: #24262A;\n"
"border: 1px solid #FFFFFF;\n"
"border-radius: 10px;\n"
"color: #FFFFFF;\n"
"\n"
"padding-left: 5px; padding-right: 3px;\n"
"\n"
"padding-top: 1px; padding-bottom: 1px;"));
        password_input_Register = new QLineEdit(Register);
        password_input_Register->setObjectName(QString::fromUtf8("password_input_Register"));
        password_input_Register->setGeometry(QRect(20, 350, 471, 41));
        password_input_Register->setStyleSheet(QString::fromUtf8("font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"font-size: 14px;\n"
"line-height: 29px;\n"
"/* identical to box height */\n"
"\n"
"\n"
"\n"
"\n"
"background: #24262A;\n"
"border: 1px solid #FFFFFF;\n"
"border-radius: 10px;\n"
"color: #FFFFFF;\n"
"\n"
"padding-left: 5px; padding-right: 3px;\n"
"\n"
"padding-top: 1px; padding-bottom: 1px;"));
        password_input_Register->setEchoMode(QLineEdit::PasswordEchoOnEdit);
        retype_password_input_Register = new QLineEdit(Register);
        retype_password_input_Register->setObjectName(QString::fromUtf8("retype_password_input_Register"));
        retype_password_input_Register->setGeometry(QRect(20, 460, 471, 41));
        retype_password_input_Register->setStyleSheet(QString::fromUtf8("font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"font-size: 14px;\n"
"line-height: 29px;\n"
"/* identical to box height */\n"
"\n"
"\n"
"\n"
"\n"
"background: #24262A;\n"
"border: 1px solid #FFFFFF;\n"
"border-radius: 10px;\n"
"color: #FFFFFF;\n"
"\n"
"padding-left: 5px; padding-right: 3px;\n"
"\n"
"padding-top: 1px; padding-bottom: 1px;"));
        retype_password_input_Register->setEchoMode(QLineEdit::PasswordEchoOnEdit);
        password_Register_2 = new QLabel(Register);
        password_Register_2->setObjectName(QString::fromUtf8("password_Register_2"));
        password_Register_2->setGeometry(QRect(20, 400, 241, 41));
        password_Register_2->setAutoFillBackground(false);
        password_Register_2->setStyleSheet(QString::fromUtf8("position: absolute;\n"
"width: 118px;\n"
"height: 29px;\n"
"left: 410px;\n"
"top: 323px;\n"
"\n"
"font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"font-size: 24px;\n"
"line-height: 29px;\n"
"/* identical to box height */\n"
"\n"
"\n"
"color: #FFFFFF;"));
        stackedWidget->addWidget(Register);
        ChangePassword = new QWidget();
        ChangePassword->setObjectName(QString::fromUtf8("ChangePassword"));
        label_ChangePassword = new QLabel(ChangePassword);
        label_ChangePassword->setObjectName(QString::fromUtf8("label_ChangePassword"));
        label_ChangePassword->setGeometry(QRect(70, 20, 441, 61));
        label_ChangePassword->setStyleSheet(QString::fromUtf8("font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"font-size: 48px;\n"
"line-height: 58px;\n"
"/* identical to box height */\n"
"\n"
"\n"
"color: #FFFFFF;"));
        label_old_password_ChangePassword = new QLabel(ChangePassword);
        label_old_password_ChangePassword->setObjectName(QString::fromUtf8("label_old_password_ChangePassword"));
        label_old_password_ChangePassword->setGeometry(QRect(60, 110, 181, 31));
        label_old_password_ChangePassword->setStyleSheet(QString::fromUtf8("font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"font-size: 24px;\n"
"line-height: 29px;\n"
"/* identical to box height */\n"
"\n"
"\n"
"color: #FFFFFF;"));
        label_new_password_ChangePassword = new QLabel(ChangePassword);
        label_new_password_ChangePassword->setObjectName(QString::fromUtf8("label_new_password_ChangePassword"));
        label_new_password_ChangePassword->setGeometry(QRect(60, 220, 181, 31));
        label_new_password_ChangePassword->setStyleSheet(QString::fromUtf8("font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"font-size: 24px;\n"
"line-height: 29px;\n"
"/* identical to box height */\n"
"\n"
"\n"
"color: #FFFFFF;"));
        label_retype_new_password_ChangePassword = new QLabel(ChangePassword);
        label_retype_new_password_ChangePassword->setObjectName(QString::fromUtf8("label_retype_new_password_ChangePassword"));
        label_retype_new_password_ChangePassword->setGeometry(QRect(60, 330, 291, 31));
        label_retype_new_password_ChangePassword->setStyleSheet(QString::fromUtf8("font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"font-size: 24px;\n"
"line-height: 29px;\n"
"/* identical to box height */\n"
"\n"
"\n"
"color: #FFFFFF;"));
        change_button_ChangePassword = new QPushButton(ChangePassword);
        change_button_ChangePassword->setObjectName(QString::fromUtf8("change_button_ChangePassword"));
        change_button_ChangePassword->setGeometry(QRect(380, 480, 101, 41));
        change_button_ChangePassword->setStyleSheet(QString::fromUtf8("border-radius: 10px;\n"
"color: #FFFFFF;\n"
"background-color: #4D92FF;\n"
""));
        back_button_ChangePassword = new QPushButton(ChangePassword);
        back_button_ChangePassword->setObjectName(QString::fromUtf8("back_button_ChangePassword"));
        back_button_ChangePassword->setGeometry(QRect(60, 480, 101, 41));
        back_button_ChangePassword->setStyleSheet(QString::fromUtf8("border-radius: 10px;\n"
"color: #4D92FF;\n"
"background-color: #FFFFFF;\n"
""));
        old_password_input_ChangePassword = new QLineEdit(ChangePassword);
        old_password_input_ChangePassword->setObjectName(QString::fromUtf8("old_password_input_ChangePassword"));
        old_password_input_ChangePassword->setGeometry(QRect(60, 160, 431, 31));
        old_password_input_ChangePassword->setStyleSheet(QString::fromUtf8("font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"font-size: 14px;\n"
"line-height: 29px;\n"
"/* identical to box height */\n"
"\n"
"\n"
"\n"
"\n"
"background: #24262A;\n"
"border: 1px solid #FFFFFF;\n"
"border-radius: 10px;\n"
"color: #FFFFFF;\n"
"\n"
"padding-left: 5px; padding-right: 3px;\n"
"\n"
"padding-top: 1px; padding-bottom: 1px;"));
        old_password_input_ChangePassword->setEchoMode(QLineEdit::PasswordEchoOnEdit);
        new_password_input_ChangePassword = new QLineEdit(ChangePassword);
        new_password_input_ChangePassword->setObjectName(QString::fromUtf8("new_password_input_ChangePassword"));
        new_password_input_ChangePassword->setGeometry(QRect(60, 270, 431, 31));
        new_password_input_ChangePassword->setStyleSheet(QString::fromUtf8("font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"font-size: 14px;\n"
"line-height: 29px;\n"
"/* identical to box height */\n"
"\n"
"\n"
"\n"
"\n"
"background: #24262A;\n"
"border: 1px solid #FFFFFF;\n"
"border-radius: 10px;\n"
"color: #FFFFFF;\n"
"\n"
"padding-left: 5px; padding-right: 3px;\n"
"\n"
"padding-top: 1px; padding-bottom: 1px;"));
        new_password_input_ChangePassword->setEchoMode(QLineEdit::PasswordEchoOnEdit);
        retype_new_password_input_ChangePassword = new QLineEdit(ChangePassword);
        retype_new_password_input_ChangePassword->setObjectName(QString::fromUtf8("retype_new_password_input_ChangePassword"));
        retype_new_password_input_ChangePassword->setGeometry(QRect(60, 390, 431, 31));
        retype_new_password_input_ChangePassword->setStyleSheet(QString::fromUtf8("font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"font-size: 14px;\n"
"line-height: 29px;\n"
"/* identical to box height */\n"
"\n"
"\n"
"\n"
"\n"
"background: #24262A;\n"
"border: 1px solid #FFFFFF;\n"
"border-radius: 10px;\n"
"color: #FFFFFF;\n"
"\n"
"padding-left: 5px; padding-right: 3px;\n"
"\n"
"padding-top: 1px; padding-bottom: 1px;"));
        retype_new_password_input_ChangePassword->setEchoMode(QLineEdit::PasswordEchoOnEdit);
        stackedWidget->addWidget(ChangePassword);
        DeleteAccount = new QWidget();
        DeleteAccount->setObjectName(QString::fromUtf8("DeleteAccount"));
        label = new QLabel(DeleteAccount);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(200, 40, 181, 111));
        label->setStyleSheet(QString::fromUtf8("\n"
"font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"font-size: 30px;\n"
"line-height: 58px;\n"
"/* identical to box height */\n"
"\n"
"\n"
"color: #FFFFFF;"));
        label_2 = new QLabel(DeleteAccount);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(100, 190, 381, 41));
        label_2->setStyleSheet(QString::fromUtf8("\n"
"font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"font-size: 20px;\n"
"line-height: 58px;\n"
"/* identical to box height */\n"
"\n"
"\n"
"color: #FFFFFF;"));
        yes_button = new QPushButton(DeleteAccount);
        yes_button->setObjectName(QString::fromUtf8("yes_button"));
        yes_button->setGeometry(QRect(370, 370, 111, 51));
        yes_button->setStyleSheet(QString::fromUtf8("border-radius: 10px;\n"
"color: #FFFFFF;\n"
"background-color: #4D92FF;\n"
""));
        no_button = new QPushButton(DeleteAccount);
        no_button->setObjectName(QString::fromUtf8("no_button"));
        no_button->setGeometry(QRect(70, 370, 111, 51));
        no_button->setStyleSheet(QString::fromUtf8("border-radius: 10px;\n"
"color: #4D92FF;\n"
"background-color: #FFFFFF;\n"
""));
        stackedWidget->addWidget(DeleteAccount);
        CreateRoom = new QWidget();
        CreateRoom->setObjectName(QString::fromUtf8("CreateRoom"));
        label_3 = new QLabel(CreateRoom);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(60, 40, 241, 31));
        label_3->setStyleSheet(QString::fromUtf8("\n"
"font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"font-size: 20px;\n"
"line-height: 58px;\n"
"/* identical to box height */\n"
"\n"
"\n"
"color: #FFFFFF;"));
        enter_room_name_CreateRoom = new QLineEdit(CreateRoom);
        enter_room_name_CreateRoom->setObjectName(QString::fromUtf8("enter_room_name_CreateRoom"));
        enter_room_name_CreateRoom->setGeometry(QRect(60, 90, 491, 41));
        enter_room_name_CreateRoom->setStyleSheet(QString::fromUtf8("font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"font-size: 14px;\n"
"line-height: 29px;\n"
"/* identical to box height */\n"
"\n"
"\n"
"\n"
"\n"
"background: #24262A;\n"
"border: 1px solid #FFFFFF;\n"
"border-radius: 10px;\n"
"color: #FFFFFF;\n"
"\n"
"padding-left: 5px; padding-right: 3px;\n"
"\n"
"padding-top: 1px; padding-bottom: 1px;"));
        list_users_are_added_CreateRoom = new QLabel(CreateRoom);
        list_users_are_added_CreateRoom->setObjectName(QString::fromUtf8("list_users_are_added_CreateRoom"));
        list_users_are_added_CreateRoom->setGeometry(QRect(70, 150, 221, 31));
        list_users_are_added_CreateRoom->setStyleSheet(QString::fromUtf8("\n"
"font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"font-size: 20px;\n"
"line-height: 58px;\n"
"/* identical to box height */\n"
"\n"
"\n"
"color: #ffffff;\n"
"background-color: #ffaaff;"));
        search_user_CreateRoom = new QLineEdit(CreateRoom);
        search_user_CreateRoom->setObjectName(QString::fromUtf8("search_user_CreateRoom"));
        search_user_CreateRoom->setGeometry(QRect(70, 192, 351, 41));
        search_user_CreateRoom->setStyleSheet(QString::fromUtf8("font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"font-size: 14px;\n"
"line-height: 29px;\n"
"/* identical to box height */\n"
"\n"
"\n"
"\n"
"\n"
"background: #24262A;\n"
"border: 1px solid #FFFFFF;\n"
"border-radius: 10px;\n"
"color: #FFFFFF;\n"
"\n"
"padding-left: 5px; padding-right: 3px;\n"
"\n"
"padding-top: 1px; padding-bottom: 1px;"));
        list_users_CreateRoom = new QListWidget(CreateRoom);
        list_users_CreateRoom->setObjectName(QString::fromUtf8("list_users_CreateRoom"));
        list_users_CreateRoom->setGeometry(QRect(70, 270, 351, 291));
        list_users_CreateRoom->setStyleSheet(QString::fromUtf8("background-color: #aeb2c8"));
        confirm_CreateRoom = new QPushButton(CreateRoom);
        confirm_CreateRoom->setObjectName(QString::fromUtf8("confirm_CreateRoom"));
        confirm_CreateRoom->setGeometry(QRect(310, 580, 80, 51));
        confirm_CreateRoom->setStyleSheet(QString::fromUtf8("border-radius: 10px;\n"
"color: #FFFFFF;\n"
"background-color: #bd9fc8"));
        cancel_CreateRoom = new QPushButton(CreateRoom);
        cancel_CreateRoom->setObjectName(QString::fromUtf8("cancel_CreateRoom"));
        cancel_CreateRoom->setGeometry(QRect(90, 580, 80, 51));
        cancel_CreateRoom->setStyleSheet(QString::fromUtf8("border-radius: 10px;\n"
"color: #FFFFFF;\n"
"background-color: #bd9fc8"));
        stackedWidget->addWidget(CreateRoom);
        RoomSetting = new QWidget();
        RoomSetting->setObjectName(QString::fromUtf8("RoomSetting"));
        add_user_RoomSetting = new QPushButton(RoomSetting);
        add_user_RoomSetting->setObjectName(QString::fromUtf8("add_user_RoomSetting"));
        add_user_RoomSetting->setGeometry(QRect(210, 490, 151, 61));
        add_user_RoomSetting->setStyleSheet(QString::fromUtf8("background-color: #47E869;radius;\n"
"border-radius: 10px;\n"
"color: #FFFFFF;\n"
"\n"
""));
        kick_user_RoomSetting = new QPushButton(RoomSetting);
        kick_user_RoomSetting->setObjectName(QString::fromUtf8("kick_user_RoomSetting"));
        kick_user_RoomSetting->setGeometry(QRect(570, 490, 141, 61));
        kick_user_RoomSetting->setStyleSheet(QString::fromUtf8("background-color: #47E869;radius;\n"
"border-radius: 10px;\n"
"color: #FFFFFF;\n"
"\n"
""));
        cancel_RoomSetting = new QPushButton(RoomSetting);
        cancel_RoomSetting->setObjectName(QString::fromUtf8("cancel_RoomSetting"));
        cancel_RoomSetting->setGeometry(QRect(30, 490, 141, 61));
        cancel_RoomSetting->setStyleSheet(QString::fromUtf8("background-color: #47E869;radius;\n"
"border-radius: 10px;\n"
"color: #FFFFFF;\n"
"\n"
""));
        modify_room_name_RoomSetting = new QPushButton(RoomSetting);
        modify_room_name_RoomSetting->setObjectName(QString::fromUtf8("modify_room_name_RoomSetting"));
        modify_room_name_RoomSetting->setGeometry(QRect(400, 490, 151, 61));
        modify_room_name_RoomSetting->setStyleSheet(QString::fromUtf8("background-color: #47E869;radius;\n"
"border-radius: 10px;\n"
"color: #FFFFFF;\n"
"\n"
""));
        stackedWidget->addWidget(RoomSetting);
        AddUser = new QWidget();
        AddUser->setObjectName(QString::fromUtf8("AddUser"));
        list_users_AddUser = new QListWidget(AddUser);
        list_users_AddUser->setObjectName(QString::fromUtf8("list_users_AddUser"));
        list_users_AddUser->setGeometry(QRect(30, 160, 301, 311));
        list_users_AddUser->setStyleSheet(QString::fromUtf8("background-color: #aeb2c8"));
        cancel_AddUser = new QPushButton(AddUser);
        cancel_AddUser->setObjectName(QString::fromUtf8("cancel_AddUser"));
        cancel_AddUser->setGeometry(QRect(10, 530, 80, 51));
        cancel_AddUser->setStyleSheet(QString::fromUtf8("border-radius: 10px;\n"
"color: #FFFFFF;\n"
"background-color: #bd9fc8"));
        confirm_AddUser = new QPushButton(AddUser);
        confirm_AddUser->setObjectName(QString::fromUtf8("confirm_AddUser"));
        confirm_AddUser->setGeometry(QRect(250, 530, 80, 51));
        confirm_AddUser->setStyleSheet(QString::fromUtf8("border-radius: 10px;\n"
"color: #FFFFFF;\n"
"background-color: #bd9fc8"));
        label_5 = new QLabel(AddUser);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(30, 10, 171, 61));
        label_5->setStyleSheet(QString::fromUtf8("\n"
"font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"font-size: 20px;\n"
"line-height: 58px;\n"
"/* identical to box height */\n"
"\n"
"\n"
"color: #FFFFFF;"));
        list_users_are_added_AddUser = new QLabel(AddUser);
        list_users_are_added_AddUser->setObjectName(QString::fromUtf8("list_users_are_added_AddUser"));
        list_users_are_added_AddUser->setGeometry(QRect(30, 90, 231, 41));
        list_users_are_added_AddUser->setStyleSheet(QString::fromUtf8("\n"
"font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"font-size: 20px;\n"
"line-height: 58px;\n"
"/* identical to box height */\n"
"\n"
"\n"
"color: #ffffff;\n"
"background-color: #ffaaff;"));
        stackedWidget->addWidget(AddUser);
        KickUser = new QWidget();
        KickUser->setObjectName(QString::fromUtf8("KickUser"));
        label_6 = new QLabel(KickUser);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(70, 40, 171, 61));
        label_6->setStyleSheet(QString::fromUtf8("\n"
"font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"font-size: 20px;\n"
"line-height: 58px;\n"
"/* identical to box height */\n"
"\n"
"\n"
"color: #FFFFFF;"));
        cancel_KickUser = new QPushButton(KickUser);
        cancel_KickUser->setObjectName(QString::fromUtf8("cancel_KickUser"));
        cancel_KickUser->setGeometry(QRect(30, 510, 80, 51));
        cancel_KickUser->setStyleSheet(QString::fromUtf8("border-radius: 10px;\n"
"color: #FFFFFF;\n"
"background-color: #bd9fc8"));
        confirm_KickUser = new QPushButton(KickUser);
        confirm_KickUser->setObjectName(QString::fromUtf8("confirm_KickUser"));
        confirm_KickUser->setGeometry(QRect(210, 510, 80, 51));
        confirm_KickUser->setStyleSheet(QString::fromUtf8("border-radius: 10px;\n"
"color: #FFFFFF;\n"
"background-color: #bd9fc8"));
        list_users_KickUser = new QListWidget(KickUser);
        list_users_KickUser->setObjectName(QString::fromUtf8("list_users_KickUser"));
        list_users_KickUser->setGeometry(QRect(50, 160, 201, 301));
        list_users_KickUser->setStyleSheet(QString::fromUtf8("background-color: #aeb2c8"));
        list_users_are_added_KickUser = new QLabel(KickUser);
        list_users_are_added_KickUser->setObjectName(QString::fromUtf8("list_users_are_added_KickUser"));
        list_users_are_added_KickUser->setGeometry(QRect(40, 110, 231, 41));
        list_users_are_added_KickUser->setStyleSheet(QString::fromUtf8("\n"
"font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"font-size: 20px;\n"
"line-height: 58px;\n"
"/* identical to box height */\n"
"\n"
"\n"
"color: #ffffff;\n"
"background-color: #ffaaff;"));
        stackedWidget->addWidget(KickUser);
        ChangeRoomName = new QWidget();
        ChangeRoomName->setObjectName(QString::fromUtf8("ChangeRoomName"));
        confirm_ChangeRoomName = new QPushButton(ChangeRoomName);
        confirm_ChangeRoomName->setObjectName(QString::fromUtf8("confirm_ChangeRoomName"));
        confirm_ChangeRoomName->setGeometry(QRect(340, 500, 80, 51));
        confirm_ChangeRoomName->setStyleSheet(QString::fromUtf8("border-radius: 10px;\n"
"color: #FFFFFF;\n"
"background-color: #bd9fc8"));
        cancel_ChangeRoomName = new QPushButton(ChangeRoomName);
        cancel_ChangeRoomName->setObjectName(QString::fromUtf8("cancel_ChangeRoomName"));
        cancel_ChangeRoomName->setGeometry(QRect(100, 500, 80, 51));
        cancel_ChangeRoomName->setStyleSheet(QString::fromUtf8("border-radius: 10px;\n"
"color: #FFFFFF;\n"
"background-color: #bd9fc8"));
        label_7 = new QLabel(ChangeRoomName);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(70, 60, 241, 31));
        label_7->setStyleSheet(QString::fromUtf8("\n"
"font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"font-size: 20px;\n"
"line-height: 58px;\n"
"/* identical to box height */\n"
"\n"
"\n"
"color: #FFFFFF;"));
        enter_new_room_name_ChangeRoomName = new QLineEdit(ChangeRoomName);
        enter_new_room_name_ChangeRoomName->setObjectName(QString::fromUtf8("enter_new_room_name_ChangeRoomName"));
        enter_new_room_name_ChangeRoomName->setGeometry(QRect(70, 110, 491, 41));
        enter_new_room_name_ChangeRoomName->setStyleSheet(QString::fromUtf8("font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"font-size: 14px;\n"
"line-height: 29px;\n"
"/* identical to box height */\n"
"\n"
"\n"
"\n"
"\n"
"background: #24262A;\n"
"border: 1px solid #FFFFFF;\n"
"border-radius: 10px;\n"
"color: #FFFFFF;\n"
"\n"
"padding-left: 5px; padding-right: 3px;\n"
"\n"
"padding-top: 1px; padding-bottom: 1px;"));
        stackedWidget->addWidget(ChangeRoomName);
        Reload = new QWidget();
        Reload->setObjectName(QString::fromUtf8("Reload"));
        label_8 = new QLabel(Reload);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(290, 250, 171, 81));
        label_8->setStyleSheet(QString::fromUtf8("\n"
"font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"font-size: 20px;\n"
"line-height: 58px;\n"
"/* identical to box height */\n"
"\n"
"\n"
"color: #FFFFFF;"));
        stackedWidget->addWidget(Reload);

        retranslateUi(ClientQT);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(ClientQT);
    } // setupUi

    void retranslateUi(QWidget *ClientQT)
    {
        ClientQT->setWindowTitle(QCoreApplication::translate("ClientQT", "ClientQT", nullptr));
        register_button_authentication->setText(QCoreApplication::translate("ClientQT", "Register", nullptr));
        exit_button_authentication->setText(QCoreApplication::translate("ClientQT", "Exit", nullptr));
        login_button_authentication->setText(QCoreApplication::translate("ClientQT", "Login", nullptr));
        label_message->setText(QCoreApplication::translate("ClientQT", "Message", nullptr));
        create_new_chat_room_button->setText(QCoreApplication::translate("ClientQT", "New Chat", nullptr));
        room_name->setText(QCoreApplication::translate("ClientQT", "Room Name", nullptr));
        room_setting_button->setText(QCoreApplication::translate("ClientQT", "Room Setting", nullptr));
        send_message_button->setText(QCoreApplication::translate("ClientQT", "OK", nullptr));
        username_button->setText(QString());
        label_4->setText(QCoreApplication::translate("ClientQT", "Login to your account", nullptr));
        username_login->setText(QCoreApplication::translate("ClientQT", "Username", nullptr));
        password_login->setText(QCoreApplication::translate("ClientQT", "Password", nullptr));
        back_button_login->setText(QCoreApplication::translate("ClientQT", "Back ", nullptr));
        confirm_login_button->setText(QCoreApplication::translate("ClientQT", "Login", nullptr));
        username_input_login->setPlaceholderText(QCoreApplication::translate("ClientQT", "Username", nullptr));
        password_input_login->setPlaceholderText(QCoreApplication::translate("ClientQT", "password", nullptr));
        back_ApplicationMenu->setText(QCoreApplication::translate("ClientQT", "Back", nullptr));
        change_password_ApplicationMenu->setText(QCoreApplication::translate("ClientQT", "Change Password", nullptr));
        delete_account_ApplicationMenu->setText(QCoreApplication::translate("ClientQT", "Delete Account", nullptr));
        logout_ApplicationMenu->setText(QCoreApplication::translate("ClientQT", "Logout", nullptr));
        label_3_Register->setText(QCoreApplication::translate("ClientQT", "Register new account", nullptr));
        username_Register->setText(QCoreApplication::translate("ClientQT", "Username", nullptr));
        password_Register->setText(QCoreApplication::translate("ClientQT", "Password", nullptr));
        back_button_Register->setText(QCoreApplication::translate("ClientQT", "Back ", nullptr));
        confirm_register_button->setText(QCoreApplication::translate("ClientQT", "Register", nullptr));
        username_input_Register->setPlaceholderText(QCoreApplication::translate("ClientQT", "username", nullptr));
        password_input_Register->setPlaceholderText(QCoreApplication::translate("ClientQT", "password", nullptr));
        retype_password_input_Register->setPlaceholderText(QCoreApplication::translate("ClientQT", "retype password", nullptr));
        password_Register_2->setText(QCoreApplication::translate("ClientQT", "Retype Password", nullptr));
        label_ChangePassword->setText(QCoreApplication::translate("ClientQT", "Change Password", nullptr));
        label_old_password_ChangePassword->setText(QCoreApplication::translate("ClientQT", "Old Password", nullptr));
        label_new_password_ChangePassword->setText(QCoreApplication::translate("ClientQT", "New Password", nullptr));
        label_retype_new_password_ChangePassword->setText(QCoreApplication::translate("ClientQT", "Retype new Password", nullptr));
        change_button_ChangePassword->setText(QCoreApplication::translate("ClientQT", "Change", nullptr));
        back_button_ChangePassword->setText(QCoreApplication::translate("ClientQT", "Back", nullptr));
        old_password_input_ChangePassword->setPlaceholderText(QCoreApplication::translate("ClientQT", "old password", nullptr));
        new_password_input_ChangePassword->setPlaceholderText(QCoreApplication::translate("ClientQT", "new passsword", nullptr));
        retype_new_password_input_ChangePassword->setPlaceholderText(QCoreApplication::translate("ClientQT", "retype new password", nullptr));
        label->setText(QCoreApplication::translate("ClientQT", "Notification", nullptr));
        label_2->setText(QCoreApplication::translate("ClientQT", "Do you want to delete your account?", nullptr));
        yes_button->setText(QCoreApplication::translate("ClientQT", "Yes", nullptr));
        no_button->setText(QCoreApplication::translate("ClientQT", "No", nullptr));
        label_3->setText(QCoreApplication::translate("ClientQT", "Create new chat room", nullptr));
        enter_room_name_CreateRoom->setText(QString());
        enter_room_name_CreateRoom->setPlaceholderText(QCoreApplication::translate("ClientQT", "Enter room name", nullptr));
        list_users_are_added_CreateRoom->setText(QString());
        search_user_CreateRoom->setText(QString());
        search_user_CreateRoom->setPlaceholderText(QCoreApplication::translate("ClientQT", "Search", nullptr));
        confirm_CreateRoom->setText(QCoreApplication::translate("ClientQT", "OK", nullptr));
        cancel_CreateRoom->setText(QCoreApplication::translate("ClientQT", "Cancel", nullptr));
        add_user_RoomSetting->setText(QCoreApplication::translate("ClientQT", "Add User", nullptr));
        kick_user_RoomSetting->setText(QCoreApplication::translate("ClientQT", "Kick User", nullptr));
        cancel_RoomSetting->setText(QCoreApplication::translate("ClientQT", "Cancel", nullptr));
        modify_room_name_RoomSetting->setText(QCoreApplication::translate("ClientQT", "Modify room name", nullptr));
        cancel_AddUser->setText(QCoreApplication::translate("ClientQT", "Cancel", nullptr));
        confirm_AddUser->setText(QCoreApplication::translate("ClientQT", "OK", nullptr));
        label_5->setText(QCoreApplication::translate("ClientQT", "Add User", nullptr));
        list_users_are_added_AddUser->setText(QString());
        label_6->setText(QCoreApplication::translate("ClientQT", "Kick User", nullptr));
        cancel_KickUser->setText(QCoreApplication::translate("ClientQT", "Cancel", nullptr));
        confirm_KickUser->setText(QCoreApplication::translate("ClientQT", "OK", nullptr));
        list_users_are_added_KickUser->setText(QString());
        confirm_ChangeRoomName->setText(QCoreApplication::translate("ClientQT", "OK", nullptr));
        cancel_ChangeRoomName->setText(QCoreApplication::translate("ClientQT", "Cancel", nullptr));
        label_7->setText(QCoreApplication::translate("ClientQT", "Change room name", nullptr));
        enter_new_room_name_ChangeRoomName->setText(QString());
        enter_new_room_name_ChangeRoomName->setPlaceholderText(QCoreApplication::translate("ClientQT", "Enter new room name", nullptr));
        label_8->setText(QCoreApplication::translate("ClientQT", "Wating ....", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ClientQT: public Ui_ClientQT {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTQT_H
