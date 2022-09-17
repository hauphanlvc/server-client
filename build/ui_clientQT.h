/********************************************************************************
** Form generated from reading UI file 'clientQT.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENTQT_H
#define UI_CLIENTQT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
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
            ClientQT->setObjectName(QStringLiteral("ClientQT"));
        ClientQT->resize(969, 767);
        stackedWidget = new QStackedWidget(ClientQT);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(90, 30, 761, 641));
        stackedWidget->setStyleSheet(QLatin1String("\n"
"background-image: url(:/image/jisoo_resize.png);\n"
"\n"
""));
        authentication = new QWidget();
        authentication->setObjectName(QStringLiteral("authentication"));
        authentication->setStyleSheet(QStringLiteral(""));
        register_button_authentication = new QPushButton(authentication);
        register_button_authentication->setObjectName(QStringLiteral("register_button_authentication"));
        register_button_authentication->setGeometry(QRect(10, 500, 151, 61));
        register_button_authentication->setStyleSheet(QLatin1String("background-color: #4D92FF;\n"
"border-radius: 10px;\n"
"color: #FFFFFF;\n"
"\n"
""));
        exit_button_authentication = new QPushButton(authentication);
        exit_button_authentication->setObjectName(QStringLiteral("exit_button_authentication"));
        exit_button_authentication->setEnabled(true);
        exit_button_authentication->setGeometry(QRect(540, 510, 141, 51));
        exit_button_authentication->setAutoFillBackground(false);
        exit_button_authentication->setStyleSheet(QLatin1String("background-color: rgb(77, 146, 255);\n"
"border-radius: 10px;\n"
"color: #FFFFFF;\n"
"\n"
""));
        exit_button_authentication->setCheckable(false);
        exit_button_authentication->setChecked(false);
        login_button_authentication = new QPushButton(authentication);
        login_button_authentication->setObjectName(QStringLiteral("login_button_authentication"));
        login_button_authentication->setGeometry(QRect(290, 500, 131, 61));
        login_button_authentication->setStyleSheet(QLatin1String("background-color: #4D92FF;\n"
"border-radius: 10px;\n"
"color: #FFFFFF;\n"
"\n"
""));
        stackedWidget->addWidget(authentication);
        ChooseRoom = new QWidget();
        ChooseRoom->setObjectName(QStringLiteral("ChooseRoom"));
        ChooseRoom->setStyleSheet(QStringLiteral(""));
        label_message = new QLabel(ChooseRoom);
        label_message->setObjectName(QStringLiteral("label_message"));
        label_message->setGeometry(QRect(60, 20, 71, 31));
        label_message->setStyleSheet(QLatin1String("\n"
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
        create_new_chat_room_button->setObjectName(QStringLiteral("create_new_chat_room_button"));
        create_new_chat_room_button->setGeometry(QRect(20, 60, 101, 31));
        create_new_chat_room_button->setStyleSheet(QLatin1String("\n"
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
        list_rooms_listWidget->setObjectName(QStringLiteral("list_rooms_listWidget"));
        list_rooms_listWidget->setGeometry(QRect(10, 110, 111, 451));
        list_rooms_listWidget->setStyleSheet(QLatin1String("\n"
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
        room_name->setObjectName(QStringLiteral("room_name"));
        room_name->setGeometry(QRect(160, 30, 91, 51));
        room_name->setStyleSheet(QLatin1String("\n"
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
        room_setting_button->setObjectName(QStringLiteral("room_setting_button"));
        room_setting_button->setGeometry(QRect(450, 30, 121, 41));
        room_setting_button->setStyleSheet(QLatin1String("\n"
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
        input_chat->setObjectName(QStringLiteral("input_chat"));
        input_chat->setGeometry(QRect(140, 530, 361, 31));
        input_chat->setStyleSheet(QLatin1String("font-family: 'Inter';\n"
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
        send_message_button->setObjectName(QStringLiteral("send_message_button"));
        send_message_button->setGeometry(QRect(519, 532, 81, 31));
        send_message_button->setStyleSheet(QLatin1String("background-color: #4D92FF;\n"
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
        list_messages_listWidget->setObjectName(QStringLiteral("list_messages_listWidget"));
        list_messages_listWidget->setGeometry(QRect(135, 111, 601, 401));
        list_messages_listWidget->setStyleSheet(QLatin1String("\n"
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
        username_button->setObjectName(QStringLiteral("username_button"));
        username_button->setGeometry(QRect(0, 20, 51, 31));
        username_button->setStyleSheet(QLatin1String("background-color: rgb(77, 146, 255);\n"
"border-radius: 10px;\n"
"color: #FFFFFF;\n"
"\n"
""));
        stackedWidget->addWidget(ChooseRoom);
        Login = new QWidget();
        Login->setObjectName(QStringLiteral("Login"));
        label_4 = new QLabel(Login);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 60, 541, 61));
        label_4->setStyleSheet(QLatin1String("position: absolute;\n"
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
        username_login->setObjectName(QStringLiteral("username_login"));
        username_login->setGeometry(QRect(20, 160, 161, 41));
        username_login->setAutoFillBackground(false);
        username_login->setStyleSheet(QLatin1String("\n"
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
        password_login->setObjectName(QStringLiteral("password_login"));
        password_login->setGeometry(QRect(30, 310, 161, 41));
        password_login->setAutoFillBackground(false);
        password_login->setStyleSheet(QLatin1String("position: absolute;\n"
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
        back_button_login->setObjectName(QStringLiteral("back_button_login"));
        back_button_login->setGeometry(QRect(40, 480, 101, 41));
        back_button_login->setStyleSheet(QLatin1String("border-radius: 10px;\n"
"color: #4D92FF;\n"
"background-color: #FFFFFF;\n"
""));
        confirm_login_button = new QPushButton(Login);
        confirm_login_button->setObjectName(QStringLiteral("confirm_login_button"));
        confirm_login_button->setGeometry(QRect(380, 480, 101, 41));
        confirm_login_button->setStyleSheet(QLatin1String("border-radius: 10px;\n"
"color: #FFFFFF;\n"
"background-color: #4D92FF;\n"
""));
        username_input_login = new QLineEdit(Login);
        username_input_login->setObjectName(QStringLiteral("username_input_login"));
        username_input_login->setGeometry(QRect(30, 220, 471, 41));
        username_input_login->setStyleSheet(QLatin1String("font-family: 'Inter';\n"
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
        password_input_login->setObjectName(QStringLiteral("password_input_login"));
        password_input_login->setGeometry(QRect(30, 380, 471, 41));
        password_input_login->setStyleSheet(QLatin1String("font-family: 'Inter';\n"
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
        ApplicationMenu->setObjectName(QStringLiteral("ApplicationMenu"));
        back_ApplicationMenu = new QPushButton(ApplicationMenu);
        back_ApplicationMenu->setObjectName(QStringLiteral("back_ApplicationMenu"));
        back_ApplicationMenu->setGeometry(QRect(30, 110, 241, 111));
        back_ApplicationMenu->setStyleSheet(QLatin1String("background-color: #4D92FF;\n"
"border-radius: 10px;\n"
"color: #FFFFFF;\n"
"\n"
""));
        change_password_ApplicationMenu = new QPushButton(ApplicationMenu);
        change_password_ApplicationMenu->setObjectName(QStringLiteral("change_password_ApplicationMenu"));
        change_password_ApplicationMenu->setGeometry(QRect(310, 110, 281, 111));
        change_password_ApplicationMenu->setStyleSheet(QLatin1String("background-color: #47E869;radius;\n"
"border-radius: 10px;\n"
"color: #FFFFFF;\n"
"\n"
""));
        delete_account_ApplicationMenu = new QPushButton(ApplicationMenu);
        delete_account_ApplicationMenu->setObjectName(QStringLiteral("delete_account_ApplicationMenu"));
        delete_account_ApplicationMenu->setGeometry(QRect(30, 280, 251, 111));
        delete_account_ApplicationMenu->setStyleSheet(QLatin1String("background-color: #EF6461;\n"
"border-radius: 10px;\n"
"color: #FFFFFF;\n"
"\n"
""));
        logout_ApplicationMenu = new QPushButton(ApplicationMenu);
        logout_ApplicationMenu->setObjectName(QStringLiteral("logout_ApplicationMenu"));
        logout_ApplicationMenu->setGeometry(QRect(310, 280, 281, 111));
        logout_ApplicationMenu->setStyleSheet(QLatin1String("background-color: #EABF67;\n"
"border-radius: 10px;\n"
"color: #FFFFFF;\n"
""));
        stackedWidget->addWidget(ApplicationMenu);
        Register = new QWidget();
        Register->setObjectName(QStringLiteral("Register"));
        label_3_Register = new QLabel(Register);
        label_3_Register->setObjectName(QStringLiteral("label_3_Register"));
        label_3_Register->setGeometry(QRect(20, 40, 541, 61));
        label_3_Register->setStyleSheet(QLatin1String("position: absolute;\n"
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
        username_Register->setObjectName(QStringLiteral("username_Register"));
        username_Register->setGeometry(QRect(20, 140, 161, 41));
        username_Register->setAutoFillBackground(false);
        username_Register->setStyleSheet(QLatin1String("position: absolute;\n"
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
        password_Register->setObjectName(QStringLiteral("password_Register"));
        password_Register->setGeometry(QRect(20, 280, 161, 41));
        password_Register->setAutoFillBackground(false);
        password_Register->setStyleSheet(QLatin1String("position: absolute;\n"
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
        back_button_Register->setObjectName(QStringLiteral("back_button_Register"));
        back_button_Register->setGeometry(QRect(10, 530, 101, 41));
        back_button_Register->setStyleSheet(QLatin1String("border-radius: 10px;\n"
"color: #4D92FF;\n"
"background-color: #FFFFFF;\n"
""));
        confirm_register_button = new QPushButton(Register);
        confirm_register_button->setObjectName(QStringLiteral("confirm_register_button"));
        confirm_register_button->setGeometry(QRect(370, 530, 101, 41));
        confirm_register_button->setStyleSheet(QLatin1String("border-radius: 10px;\n"
"color: #FFFFFF;\n"
"background-color: #4D92FF;\n"
""));
        username_input_Register = new QLineEdit(Register);
        username_input_Register->setObjectName(QStringLiteral("username_input_Register"));
        username_input_Register->setGeometry(QRect(20, 210, 471, 41));
        username_input_Register->setStyleSheet(QLatin1String("font-family: 'Inter';\n"
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
        password_input_Register->setObjectName(QStringLiteral("password_input_Register"));
        password_input_Register->setGeometry(QRect(20, 350, 471, 41));
        password_input_Register->setStyleSheet(QLatin1String("font-family: 'Inter';\n"
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
        retype_password_input_Register->setObjectName(QStringLiteral("retype_password_input_Register"));
        retype_password_input_Register->setGeometry(QRect(20, 460, 471, 41));
        retype_password_input_Register->setStyleSheet(QLatin1String("font-family: 'Inter';\n"
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
        password_Register_2->setObjectName(QStringLiteral("password_Register_2"));
        password_Register_2->setGeometry(QRect(20, 400, 241, 41));
        password_Register_2->setAutoFillBackground(false);
        password_Register_2->setStyleSheet(QLatin1String("position: absolute;\n"
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
        ChangePassword->setObjectName(QStringLiteral("ChangePassword"));
        label_ChangePassword = new QLabel(ChangePassword);
        label_ChangePassword->setObjectName(QStringLiteral("label_ChangePassword"));
        label_ChangePassword->setGeometry(QRect(70, 20, 441, 61));
        label_ChangePassword->setStyleSheet(QLatin1String("font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"font-size: 48px;\n"
"line-height: 58px;\n"
"/* identical to box height */\n"
"\n"
"\n"
"color: #FFFFFF;"));
        label_old_password_ChangePassword = new QLabel(ChangePassword);
        label_old_password_ChangePassword->setObjectName(QStringLiteral("label_old_password_ChangePassword"));
        label_old_password_ChangePassword->setGeometry(QRect(60, 110, 181, 31));
        label_old_password_ChangePassword->setStyleSheet(QLatin1String("font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"font-size: 24px;\n"
"line-height: 29px;\n"
"/* identical to box height */\n"
"\n"
"\n"
"color: #FFFFFF;"));
        label_new_password_ChangePassword = new QLabel(ChangePassword);
        label_new_password_ChangePassword->setObjectName(QStringLiteral("label_new_password_ChangePassword"));
        label_new_password_ChangePassword->setGeometry(QRect(60, 220, 181, 31));
        label_new_password_ChangePassword->setStyleSheet(QLatin1String("font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"font-size: 24px;\n"
"line-height: 29px;\n"
"/* identical to box height */\n"
"\n"
"\n"
"color: #FFFFFF;"));
        label_retype_new_password_ChangePassword = new QLabel(ChangePassword);
        label_retype_new_password_ChangePassword->setObjectName(QStringLiteral("label_retype_new_password_ChangePassword"));
        label_retype_new_password_ChangePassword->setGeometry(QRect(60, 330, 291, 31));
        label_retype_new_password_ChangePassword->setStyleSheet(QLatin1String("font-family: 'Inter';\n"
"font-style: normal;\n"
"font-weight: 500;\n"
"font-size: 24px;\n"
"line-height: 29px;\n"
"/* identical to box height */\n"
"\n"
"\n"
"color: #FFFFFF;"));
        change_button_ChangePassword = new QPushButton(ChangePassword);
        change_button_ChangePassword->setObjectName(QStringLiteral("change_button_ChangePassword"));
        change_button_ChangePassword->setGeometry(QRect(380, 480, 101, 41));
        change_button_ChangePassword->setStyleSheet(QLatin1String("border-radius: 10px;\n"
"color: #FFFFFF;\n"
"background-color: #4D92FF;\n"
""));
        back_button_ChangePassword = new QPushButton(ChangePassword);
        back_button_ChangePassword->setObjectName(QStringLiteral("back_button_ChangePassword"));
        back_button_ChangePassword->setGeometry(QRect(60, 480, 101, 41));
        back_button_ChangePassword->setStyleSheet(QLatin1String("border-radius: 10px;\n"
"color: #4D92FF;\n"
"background-color: #FFFFFF;\n"
""));
        old_password_input_ChangePassword = new QLineEdit(ChangePassword);
        old_password_input_ChangePassword->setObjectName(QStringLiteral("old_password_input_ChangePassword"));
        old_password_input_ChangePassword->setGeometry(QRect(60, 160, 431, 31));
        old_password_input_ChangePassword->setStyleSheet(QLatin1String("font-family: 'Inter';\n"
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
        new_password_input_ChangePassword->setObjectName(QStringLiteral("new_password_input_ChangePassword"));
        new_password_input_ChangePassword->setGeometry(QRect(60, 270, 431, 31));
        new_password_input_ChangePassword->setStyleSheet(QLatin1String("font-family: 'Inter';\n"
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
        retype_new_password_input_ChangePassword->setObjectName(QStringLiteral("retype_new_password_input_ChangePassword"));
        retype_new_password_input_ChangePassword->setGeometry(QRect(60, 390, 431, 31));
        retype_new_password_input_ChangePassword->setStyleSheet(QLatin1String("font-family: 'Inter';\n"
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
        DeleteAccount->setObjectName(QStringLiteral("DeleteAccount"));
        label = new QLabel(DeleteAccount);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(200, 40, 181, 111));
        label->setStyleSheet(QLatin1String("\n"
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
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(100, 190, 381, 41));
        label_2->setStyleSheet(QLatin1String("\n"
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
        yes_button->setObjectName(QStringLiteral("yes_button"));
        yes_button->setGeometry(QRect(370, 370, 111, 51));
        yes_button->setStyleSheet(QLatin1String("border-radius: 10px;\n"
"color: #FFFFFF;\n"
"background-color: #4D92FF;\n"
""));
        no_button = new QPushButton(DeleteAccount);
        no_button->setObjectName(QStringLiteral("no_button"));
        no_button->setGeometry(QRect(70, 370, 111, 51));
        no_button->setStyleSheet(QLatin1String("border-radius: 10px;\n"
"color: #4D92FF;\n"
"background-color: #FFFFFF;\n"
""));
        stackedWidget->addWidget(DeleteAccount);
        CreateRoom = new QWidget();
        CreateRoom->setObjectName(QStringLiteral("CreateRoom"));
        label_3 = new QLabel(CreateRoom);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(60, 40, 241, 31));
        label_3->setStyleSheet(QLatin1String("\n"
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
        enter_room_name_CreateRoom->setObjectName(QStringLiteral("enter_room_name_CreateRoom"));
        enter_room_name_CreateRoom->setGeometry(QRect(60, 90, 491, 41));
        enter_room_name_CreateRoom->setStyleSheet(QLatin1String("font-family: 'Inter';\n"
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
        list_users_are_added_CreateRoom->setObjectName(QStringLiteral("list_users_are_added_CreateRoom"));
        list_users_are_added_CreateRoom->setGeometry(QRect(70, 150, 221, 31));
        list_users_are_added_CreateRoom->setStyleSheet(QLatin1String("\n"
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
        search_user_CreateRoom->setObjectName(QStringLiteral("search_user_CreateRoom"));
        search_user_CreateRoom->setGeometry(QRect(70, 192, 351, 41));
        search_user_CreateRoom->setStyleSheet(QLatin1String("font-family: 'Inter';\n"
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
        list_users_CreateRoom->setObjectName(QStringLiteral("list_users_CreateRoom"));
        list_users_CreateRoom->setGeometry(QRect(70, 270, 351, 291));
        list_users_CreateRoom->setStyleSheet(QStringLiteral("background-color: #aeb2c8"));
        confirm_CreateRoom = new QPushButton(CreateRoom);
        confirm_CreateRoom->setObjectName(QStringLiteral("confirm_CreateRoom"));
        confirm_CreateRoom->setGeometry(QRect(310, 580, 80, 51));
        confirm_CreateRoom->setStyleSheet(QLatin1String("border-radius: 10px;\n"
"color: #FFFFFF;\n"
"background-color: #bd9fc8"));
        cancel_CreateRoom = new QPushButton(CreateRoom);
        cancel_CreateRoom->setObjectName(QStringLiteral("cancel_CreateRoom"));
        cancel_CreateRoom->setGeometry(QRect(90, 580, 80, 51));
        cancel_CreateRoom->setStyleSheet(QLatin1String("border-radius: 10px;\n"
"color: #FFFFFF;\n"
"background-color: #bd9fc8"));
        stackedWidget->addWidget(CreateRoom);
        RoomSetting = new QWidget();
        RoomSetting->setObjectName(QStringLiteral("RoomSetting"));
        add_user_RoomSetting = new QPushButton(RoomSetting);
        add_user_RoomSetting->setObjectName(QStringLiteral("add_user_RoomSetting"));
        add_user_RoomSetting->setGeometry(QRect(210, 490, 151, 61));
        add_user_RoomSetting->setStyleSheet(QLatin1String("background-color: #47E869;radius;\n"
"border-radius: 10px;\n"
"color: #FFFFFF;\n"
"\n"
""));
        kick_user_RoomSetting = new QPushButton(RoomSetting);
        kick_user_RoomSetting->setObjectName(QStringLiteral("kick_user_RoomSetting"));
        kick_user_RoomSetting->setGeometry(QRect(570, 490, 141, 61));
        kick_user_RoomSetting->setStyleSheet(QLatin1String("background-color: #47E869;radius;\n"
"border-radius: 10px;\n"
"color: #FFFFFF;\n"
"\n"
""));
        cancel_RoomSetting = new QPushButton(RoomSetting);
        cancel_RoomSetting->setObjectName(QStringLiteral("cancel_RoomSetting"));
        cancel_RoomSetting->setGeometry(QRect(30, 490, 141, 61));
        cancel_RoomSetting->setStyleSheet(QLatin1String("background-color: #47E869;radius;\n"
"border-radius: 10px;\n"
"color: #FFFFFF;\n"
"\n"
""));
        modify_room_name_RoomSetting = new QPushButton(RoomSetting);
        modify_room_name_RoomSetting->setObjectName(QStringLiteral("modify_room_name_RoomSetting"));
        modify_room_name_RoomSetting->setGeometry(QRect(400, 490, 151, 61));
        modify_room_name_RoomSetting->setStyleSheet(QLatin1String("background-color: #47E869;radius;\n"
"border-radius: 10px;\n"
"color: #FFFFFF;\n"
"\n"
""));
        stackedWidget->addWidget(RoomSetting);
        AddUser = new QWidget();
        AddUser->setObjectName(QStringLiteral("AddUser"));
        list_users_AddUser = new QListWidget(AddUser);
        list_users_AddUser->setObjectName(QStringLiteral("list_users_AddUser"));
        list_users_AddUser->setGeometry(QRect(30, 160, 301, 311));
        list_users_AddUser->setStyleSheet(QStringLiteral("background-color: #aeb2c8"));
        cancel_AddUser = new QPushButton(AddUser);
        cancel_AddUser->setObjectName(QStringLiteral("cancel_AddUser"));
        cancel_AddUser->setGeometry(QRect(10, 530, 80, 51));
        cancel_AddUser->setStyleSheet(QLatin1String("border-radius: 10px;\n"
"color: #FFFFFF;\n"
"background-color: #bd9fc8"));
        confirm_AddUser = new QPushButton(AddUser);
        confirm_AddUser->setObjectName(QStringLiteral("confirm_AddUser"));
        confirm_AddUser->setGeometry(QRect(250, 530, 80, 51));
        confirm_AddUser->setStyleSheet(QLatin1String("border-radius: 10px;\n"
"color: #FFFFFF;\n"
"background-color: #bd9fc8"));
        label_5 = new QLabel(AddUser);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(30, 10, 171, 61));
        label_5->setStyleSheet(QLatin1String("\n"
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
        list_users_are_added_AddUser->setObjectName(QStringLiteral("list_users_are_added_AddUser"));
        list_users_are_added_AddUser->setGeometry(QRect(30, 90, 231, 41));
        list_users_are_added_AddUser->setStyleSheet(QLatin1String("\n"
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
        KickUser->setObjectName(QStringLiteral("KickUser"));
        label_6 = new QLabel(KickUser);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(70, 40, 171, 61));
        label_6->setStyleSheet(QLatin1String("\n"
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
        cancel_KickUser->setObjectName(QStringLiteral("cancel_KickUser"));
        cancel_KickUser->setGeometry(QRect(30, 510, 80, 51));
        cancel_KickUser->setStyleSheet(QLatin1String("border-radius: 10px;\n"
"color: #FFFFFF;\n"
"background-color: #bd9fc8"));
        confirm_KickUser = new QPushButton(KickUser);
        confirm_KickUser->setObjectName(QStringLiteral("confirm_KickUser"));
        confirm_KickUser->setGeometry(QRect(210, 510, 80, 51));
        confirm_KickUser->setStyleSheet(QLatin1String("border-radius: 10px;\n"
"color: #FFFFFF;\n"
"background-color: #bd9fc8"));
        list_users_KickUser = new QListWidget(KickUser);
        list_users_KickUser->setObjectName(QStringLiteral("list_users_KickUser"));
        list_users_KickUser->setGeometry(QRect(50, 160, 201, 301));
        list_users_KickUser->setStyleSheet(QStringLiteral("background-color: #aeb2c8"));
        list_users_are_added_KickUser = new QLabel(KickUser);
        list_users_are_added_KickUser->setObjectName(QStringLiteral("list_users_are_added_KickUser"));
        list_users_are_added_KickUser->setGeometry(QRect(40, 110, 231, 41));
        list_users_are_added_KickUser->setStyleSheet(QLatin1String("\n"
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
        ChangeRoomName->setObjectName(QStringLiteral("ChangeRoomName"));
        confirm_ChangeRoomName = new QPushButton(ChangeRoomName);
        confirm_ChangeRoomName->setObjectName(QStringLiteral("confirm_ChangeRoomName"));
        confirm_ChangeRoomName->setGeometry(QRect(340, 500, 80, 51));
        confirm_ChangeRoomName->setStyleSheet(QLatin1String("border-radius: 10px;\n"
"color: #FFFFFF;\n"
"background-color: #bd9fc8"));
        cancel_ChangeRoomName = new QPushButton(ChangeRoomName);
        cancel_ChangeRoomName->setObjectName(QStringLiteral("cancel_ChangeRoomName"));
        cancel_ChangeRoomName->setGeometry(QRect(100, 500, 80, 51));
        cancel_ChangeRoomName->setStyleSheet(QLatin1String("border-radius: 10px;\n"
"color: #FFFFFF;\n"
"background-color: #bd9fc8"));
        label_7 = new QLabel(ChangeRoomName);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(70, 60, 241, 31));
        label_7->setStyleSheet(QLatin1String("\n"
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
        enter_new_room_name_ChangeRoomName->setObjectName(QStringLiteral("enter_new_room_name_ChangeRoomName"));
        enter_new_room_name_ChangeRoomName->setGeometry(QRect(70, 110, 491, 41));
        enter_new_room_name_ChangeRoomName->setStyleSheet(QLatin1String("font-family: 'Inter';\n"
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
        Reload->setObjectName(QStringLiteral("Reload"));
        label_8 = new QLabel(Reload);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(290, 250, 171, 81));
        label_8->setStyleSheet(QLatin1String("\n"
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
        ClientQT->setWindowTitle(QApplication::translate("ClientQT", "ClientQT", Q_NULLPTR));
        register_button_authentication->setText(QApplication::translate("ClientQT", "Register", Q_NULLPTR));
        exit_button_authentication->setText(QApplication::translate("ClientQT", "Exit", Q_NULLPTR));
        login_button_authentication->setText(QApplication::translate("ClientQT", "Login", Q_NULLPTR));
        label_message->setText(QApplication::translate("ClientQT", "Message", Q_NULLPTR));
        create_new_chat_room_button->setText(QApplication::translate("ClientQT", "New Chat", Q_NULLPTR));
        room_name->setText(QApplication::translate("ClientQT", "Room Name", Q_NULLPTR));
        room_setting_button->setText(QApplication::translate("ClientQT", "Room Setting", Q_NULLPTR));
        send_message_button->setText(QApplication::translate("ClientQT", "OK", Q_NULLPTR));
        username_button->setText(QString());
        label_4->setText(QApplication::translate("ClientQT", "Login to your account", Q_NULLPTR));
        username_login->setText(QApplication::translate("ClientQT", "Username", Q_NULLPTR));
        password_login->setText(QApplication::translate("ClientQT", "Password", Q_NULLPTR));
        back_button_login->setText(QApplication::translate("ClientQT", "Back ", Q_NULLPTR));
        confirm_login_button->setText(QApplication::translate("ClientQT", "Login", Q_NULLPTR));
        username_input_login->setPlaceholderText(QApplication::translate("ClientQT", "Username", Q_NULLPTR));
        password_input_login->setPlaceholderText(QApplication::translate("ClientQT", "password", Q_NULLPTR));
        back_ApplicationMenu->setText(QApplication::translate("ClientQT", "Back", Q_NULLPTR));
        change_password_ApplicationMenu->setText(QApplication::translate("ClientQT", "Change Password", Q_NULLPTR));
        delete_account_ApplicationMenu->setText(QApplication::translate("ClientQT", "Delete Account", Q_NULLPTR));
        logout_ApplicationMenu->setText(QApplication::translate("ClientQT", "Logout", Q_NULLPTR));
        label_3_Register->setText(QApplication::translate("ClientQT", "Register new account", Q_NULLPTR));
        username_Register->setText(QApplication::translate("ClientQT", "Username", Q_NULLPTR));
        password_Register->setText(QApplication::translate("ClientQT", "Password", Q_NULLPTR));
        back_button_Register->setText(QApplication::translate("ClientQT", "Back ", Q_NULLPTR));
        confirm_register_button->setText(QApplication::translate("ClientQT", "Register", Q_NULLPTR));
        username_input_Register->setPlaceholderText(QApplication::translate("ClientQT", "username", Q_NULLPTR));
        password_input_Register->setPlaceholderText(QApplication::translate("ClientQT", "password", Q_NULLPTR));
        retype_password_input_Register->setPlaceholderText(QApplication::translate("ClientQT", "retype password", Q_NULLPTR));
        password_Register_2->setText(QApplication::translate("ClientQT", "Retype Password", Q_NULLPTR));
        label_ChangePassword->setText(QApplication::translate("ClientQT", "Change Password", Q_NULLPTR));
        label_old_password_ChangePassword->setText(QApplication::translate("ClientQT", "Old Password", Q_NULLPTR));
        label_new_password_ChangePassword->setText(QApplication::translate("ClientQT", "New Password", Q_NULLPTR));
        label_retype_new_password_ChangePassword->setText(QApplication::translate("ClientQT", "Retype new Password", Q_NULLPTR));
        change_button_ChangePassword->setText(QApplication::translate("ClientQT", "Change", Q_NULLPTR));
        back_button_ChangePassword->setText(QApplication::translate("ClientQT", "Back", Q_NULLPTR));
        old_password_input_ChangePassword->setPlaceholderText(QApplication::translate("ClientQT", "old password", Q_NULLPTR));
        new_password_input_ChangePassword->setPlaceholderText(QApplication::translate("ClientQT", "new passsword", Q_NULLPTR));
        retype_new_password_input_ChangePassword->setPlaceholderText(QApplication::translate("ClientQT", "retype new password", Q_NULLPTR));
        label->setText(QApplication::translate("ClientQT", "Notification", Q_NULLPTR));
        label_2->setText(QApplication::translate("ClientQT", "Do you want to delete your account?", Q_NULLPTR));
        yes_button->setText(QApplication::translate("ClientQT", "Yes", Q_NULLPTR));
        no_button->setText(QApplication::translate("ClientQT", "No", Q_NULLPTR));
        label_3->setText(QApplication::translate("ClientQT", "Create new chat room", Q_NULLPTR));
        enter_room_name_CreateRoom->setText(QString());
        enter_room_name_CreateRoom->setPlaceholderText(QApplication::translate("ClientQT", "Enter room name", Q_NULLPTR));
        list_users_are_added_CreateRoom->setText(QString());
        search_user_CreateRoom->setText(QString());
        search_user_CreateRoom->setPlaceholderText(QApplication::translate("ClientQT", "Search", Q_NULLPTR));
        confirm_CreateRoom->setText(QApplication::translate("ClientQT", "OK", Q_NULLPTR));
        cancel_CreateRoom->setText(QApplication::translate("ClientQT", "Cancel", Q_NULLPTR));
        add_user_RoomSetting->setText(QApplication::translate("ClientQT", "Add User", Q_NULLPTR));
        kick_user_RoomSetting->setText(QApplication::translate("ClientQT", "Kick User", Q_NULLPTR));
        cancel_RoomSetting->setText(QApplication::translate("ClientQT", "Cancel", Q_NULLPTR));
        modify_room_name_RoomSetting->setText(QApplication::translate("ClientQT", "Modify room name", Q_NULLPTR));
        cancel_AddUser->setText(QApplication::translate("ClientQT", "Cancel", Q_NULLPTR));
        confirm_AddUser->setText(QApplication::translate("ClientQT", "OK", Q_NULLPTR));
        label_5->setText(QApplication::translate("ClientQT", "Add User", Q_NULLPTR));
        list_users_are_added_AddUser->setText(QString());
        label_6->setText(QApplication::translate("ClientQT", "Kick User", Q_NULLPTR));
        cancel_KickUser->setText(QApplication::translate("ClientQT", "Cancel", Q_NULLPTR));
        confirm_KickUser->setText(QApplication::translate("ClientQT", "OK", Q_NULLPTR));
        list_users_are_added_KickUser->setText(QString());
        confirm_ChangeRoomName->setText(QApplication::translate("ClientQT", "OK", Q_NULLPTR));
        cancel_ChangeRoomName->setText(QApplication::translate("ClientQT", "Cancel", Q_NULLPTR));
        label_7->setText(QApplication::translate("ClientQT", "Change room name", Q_NULLPTR));
        enter_new_room_name_ChangeRoomName->setText(QString());
        enter_new_room_name_ChangeRoomName->setPlaceholderText(QApplication::translate("ClientQT", "Enter new room name", Q_NULLPTR));
        label_8->setText(QApplication::translate("ClientQT", "Wating ....", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ClientQT: public Ui_ClientQT {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTQT_H
