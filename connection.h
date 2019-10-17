#ifndef CONNECTION_H
#define CONNECTION_H
#include "dialog.h"
#include <QTcpSocket>
#include <QObject>

class connection:public QObject
{
    Q_OBJECT
public:
    explicit connection(QWidget *parent = 0);
    ~connection();
    bool set_tcpclient();
    void set_quit_tcpclient();
    bool set_tcpserve();
    void set_IP(const QString ip);
    void set_Port(const unsigned int por);
    QString getip()const;
    unsigned int getport()const;
    unsigned int getLocalPort()const;
    QTcpSocket *get_socket()const;

    friend void free_socket(connection *cnt);
private:
    QTcpSocket *socket ;
    QString IP;
    unsigned int local_port;
    unsigned int port ;


};

#endif // CONNECTION_H
