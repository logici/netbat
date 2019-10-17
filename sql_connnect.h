#ifndef SQL_CONNNECT_H
#define SQL_CONNNECT_H

#include <QSqlDatabase>     //数据库，需要该数据库的驱动
#include <QSqlQuery>        //
#include <QMessageBox>


static bool create_sqlconnection()
{
    //我们这里使用的是mydql
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");    //默认的本地主机，ip号为127.0.0.1
    db.setDatabaseName("myprogram");    //需要操作的数据库
    db.setUserName("root");
    db.setPort(3307);       //默认为3306
    db.setPassword("mysql123");

    //打开这样的数据库
    if(!db.open())
    {
        QMessageBox::critical(0,QObject::tr("无法打开数据库"),
                              "无法创建数据库连接！",QMessageBox::Cancel);
        return false;
    }

    //QString str = QString("create table UesrMessage (id int primary key,"
      //                    "%1 varchar(20),passward varchar(20)").arg("user");


    //****************存在了不会重新创建
    //****************登陆信息表
    //qDebug()<<str;                      //调试使用
    //str = QString("insert into UserMessage values(%1,'%2','%3')").arg(0).arg("hehe").arg("123");
    //qDebug()<<str;
    //打开了数据库则执行一下的创建表操作
    QSqlQuery query(db);        //使用这个类可以使用SQL的语言
    query.exec("set name 'utf8'");  //这个是sql的语言，支持中文

    query.exec("create table UserMessage (user varchar(20) primary key,passward varchar(20))");
   // query.exec(str);

  //  query.exec("select *from usermessage");
  //  id_nuber = query.size();

    //**************数据采集表
    query.exec("create table temperature (Data datetime(6) primary key,Temperature float NOT NULL)");
    return true;
}

#endif // SQL_CONNNECT_H
