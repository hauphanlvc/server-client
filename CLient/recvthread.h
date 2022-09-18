#ifndef RECVTHREAD_H
#define RECVTHREAD_H

#include <QObject>
#include <QThread>
#include "client.h"
#include <iostream>
#include <QMutex>
#include "clientQT.h"

class Client;
class ClientQT;
class RecvThread : public QThread
{
    Q_OBJECT
public:
    // Client *client;

    ClientQT *clientQT;
    explicit RecvThread(QObject *parent , ClientQT *clientQT);
    void run();
signals:
    void NewMessage(QString);
};

#endif // RECVTHREAD_H