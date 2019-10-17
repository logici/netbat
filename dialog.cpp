#include <QMessageBox>
#include <QApplication>
#include <QEvent>
#include "dialog.h"
#include "connection.h"
extern bool ack;

dialog::dialog(QWidget *parent)
{
    dia = new QDialog(parent);
}
dialog::~dialog()
{
   // delete dia;
}

bool dialog::dia_tcp_client()
{

    dia->setWindowTitle(QObject::tr("设置所要连接的IP和端口"));     //标题
    dia->setMinimumSize(350,150);        //设置对话框大小
    dia->setMaximumSize(350,150);

    //************标签IP port
    label_IP = new QLabel(dia);
    label_Port = new QLabel(dia);
    label_IP->setText(QObject::tr("IP:"));
    label_Port->setText(QObject::tr("Port:"));
    label_IP->setGeometry(QRect(100,40,30,20));
    label_Port->setGeometry(QRect(100,70,30,20));

    //************Edit
    IP_edit = new QLineEdit(dia);
    Port_edit = new QLineEdit(dia);
    IP_edit->setText(QObject::tr("127.0.0.1"));
    Port_edit->setText(QObject::tr("11100"));
    IP_edit->setGeometry(QRect(140,40,100,20));
    Port_edit->setGeometry(QRect(140,70,100,20));

    //************PushButton
    btn_ok = new QPushButton(dia);
    btn_cel = new QPushButton(dia);
    btn_ok->setText(QObject::tr("OK"));
    btn_cel->setText(QObject::tr("Concel"));
    btn_ok->setGeometry(QRect(70,120,80,30));
    btn_cel->setGeometry(QRect(205,120,80,30));

    //dialog->setSizeGripEnabled(true);        //使能大小设置
    //dia->setModal(false);
    //dia->show();
    QObject::connect(btn_cel, SIGNAL(clicked()), dia, SLOT(reject()));
    //QObject::connect(this->btn_cel,&QPushButton::clicked,this,&QDialog::reject);
    QObject::connect(btn_ok,&QPushButton::clicked,this,&dialog::get_IP);
    if(dia->exec() == dia->Accepted)        //阻塞点
    {
        qDebug()<<1;
        emit enter_tcpclient();
        return true;
    }else return false ;
}

//问题！！！！！！！！！！！！！！！！！！！！！！！！！！
//不能在一个类里调用另一个类的槽函数？？？
//那我应该怎么关闭对话框？？？？？？？？？？？？？？？？


//槽函数
void dialog::get_IP()
{
    //读取编辑栏上的ip
    getip = IP_edit->text();
    getport = Port_edit->text().toInt();
    QMessageBox::warning(dia,tr("成功"),"设置成功",QMessageBox::Ok);
    dia->accept();              //Qdialog的实例对象释放对话框
    //qDebug()<<this->getip;
}

QString dialog::getIpToCtn()const
{
    return getip;
}

unsigned int dialog::getPortToctn()const
{
    return getport;
}

//友元函数
void free_dialog(dialog *d)
{
    delete d->dia;
}
