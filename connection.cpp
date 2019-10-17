#include "connection.h"
#include <QDebug>
#include <QHostAddress>

connection::connection(QWidget *parent)
{
    socket = new QTcpSocket(parent);    //实例套接字
}

connection::~connection()
{
    //作用域的问题？？
   // delete socket;
}

bool connection::set_tcpclient()
{
    //QString local_ip ;
    //socket->abort();            //取消已有的连接
    socket->connectToHost(IP,port); //连接上服务器
    if(!socket->waitForConnected(1000)) //等待连接上
    {
        qDebug()<<"false!";
        return false;
    }
    qDebug()<<"successful!";
    local_port = socket->localPort();
   // local_ip = socket->localAddress().toString();
    //qDebug()<<local_port<<local_ip;
    return true;
}

void connection::set_quit_tcpclient()
{
    socket->disconnectFromHost();
}

bool connection::set_tcpserve()
{
    //port = 11100;           //所要监听的某个端口

}

void connection::set_IP(const QString ip)
{
    IP = ip;
}

void connection::set_Port(const unsigned int por)
{
    port = por;
}

//友元函数
void free_socket(connection *cnt)
{
    delete cnt->socket;
}

QString connection::getip()const
{
    return IP;
}

unsigned int connection::getport()const
{
    return port;
}

unsigned int connection::getLocalPort()const
{
    return local_port;
}

QTcpSocket *connection::get_socket()const
{
    return socket;
}
