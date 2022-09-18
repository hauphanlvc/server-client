#include "recvthread.h"
RecvThread::RecvThread(QObject *parent,ClientQT *clientQT):
        QThread(parent)
{
    
    this->clientQT = clientQT;
}
void RecvThread::run() {
    
    cout << "^^^^^^^^^^^^^^^\n"; 
    
    // exec();
    while (!this->currentThread()->isInterruptionRequested())
    {
        //  if (  ) {
        //         cout << "Thoat Thread\n";
        //     return;
        //     }
        
        // auto message = client->RecvMessage();
        // if (message.first <=0 ) {
        //     cout << "message is empty\n";
        //     continue;
        //     }
        auto message = clientQT->RecvMessage(clientQT->message);
        if (message.second == "EXIT_THREAD") {
            cout << "EXIT_THREAD" << endl;

            return ;
        }
        if (message.second == "#send_success") continue;
        cout << "message when recv in QThread: " << message.second << "\n";
        // usleep(10000);
        emit NewMessage(QString::fromStdString(message.second));
        // exec();
       
    }
    
    cout << "Thoat Thread\n";
    cout << "<<<<<<<<<<<<<<<<\n";
    exec();
    
}