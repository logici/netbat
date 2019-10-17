#include "login_dialog.h"
#include "logindialog_ui.h"
#include "sql_connnect.h"
#include <QSqlDatabase>
#include <QMessageBox>
#include <QDebug>
//extern int id_nuber;
login_dialog::login_dialog(QWidget *parent)
    :QDialog(parent),
    login_dia(new Ui::login_dialog)
{
    login_dia->setupUi(this);

}

login_dialog::~login_dialog()
{
    delete login_dia;
}


void login_dialog::on_loginBtn_clicked()
{
    // 判断用户名和密码是否正确，如果错误则弹出警告对话框
    if(login_dia->usrLineEdit->text().isEmpty())
    {
        QMessageBox::critical(0,tr("失败"),"账号不能为空",QMessageBox::Cancel);
        login_dia->usrLineEdit->setFocus();
    }
    else if(login_dia->pwdLineEdit->text().isEmpty())
    {
        QMessageBox::critical(0,tr("失败"),"密码不能为空",QMessageBox::Cancel);
        login_dia->pwdLineEdit->setFocus();
    }
    else{
        QString user = login_dia->usrLineEdit->text();
        QString str = QString("select passward from usermessage where user = '%1'").arg(user);
        qDebug()<<str;
        QSqlQuery query;
        query.exec(str);
        if(query.size() == 0)
        {
            QMessageBox::warning(this, tr("账号不存在"),
                                             tr("请输入正确的账号再登录！"), QMessageBox::Ok);
        }
        else{
            //返回的recoder value是指在recoder集的前面，也即还没有指向记录
            //需要一个next()指向下面的记录
            query.next();
            if(query.value(0).toString() == login_dia->pwdLineEdit->text())
            {
               QDialog::accept();
            }else{
                QMessageBox::warning(this, tr("密码错误"),
                                                 tr("请输入正确的密码再登录！"), QMessageBox::Ok);
                login_dia->pwdLineEdit->setFocus();
            }
        }
    }
}

//注册
void login_dialog::on_logonBtn_clicked()
{

    if(login_dia->usrLineEdit->text().isEmpty() && login_dia->pwdLineEdit->text().isEmpty() )
        QMessageBox::critical(0,tr("失败"),"账号或密码不能为空",QMessageBox::Cancel);
    else{
     QString user = login_dia->usrLineEdit->text();
     QString pwd = login_dia->pwdLineEdit->text();
     QSqlQuery query;
     QString str = QString("insert into UserMessage values('%1','%2')").arg(user).arg(pwd);
     qDebug()<<str;

     if(!query.exec(str))
         QMessageBox::warning(0,tr("失败"),"该账号已被注册，请重新输入",QMessageBox::Ok);
     else
     {
         QMessageBox::warning(0,tr("成功"),"注册成功",QMessageBox::Ok);
     }
    }
}
