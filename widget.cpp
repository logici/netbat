
#include <time.h>
#include <QDateTime>
#include "sql_connnect.h"
#include "widget.h"
#include "ui_widget.h"

//#define inf 0x3f3f3f3f  //哨兵
//int _max0 = 0;      //最大值
//int _min0 = inf;    //最小值
const int maxlength = 30;
#define random(x) (rand()%x)

void right_to(float *p);
bool save_intosql(const QDateTime &dat,const int *ptr);
bool is_digits(const std::string &str);
void protocol(const QByteArray &buf);
void get_srand();
bool delay();
void msecSleep(int msec);
void msecSleep1(int msec);
//#include "connection.h"
bool ack;

int a[2];
float b[maxlength];
float temp_num;
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->tem_plot->setHidden(true);
    ui->group_graph->setHidden(true);
    ctn =  new connection ;

    group_socket = new QGroupBox(this);
    group_socket->setHidden(true);

    group_get_msg = new QGroupBox(this);
    group_get_msg->setHidden(true);
    group_send_msg = new QGroupBox(this);
    group_send_msg->setHidden(true);

  //  group_graph = new QGroupBox(this);
  //  group_graph->setHidden(true);

    label_ip = new QLabel(group_socket);        //标签  用以显示给用户
    label_port = new QLabel(group_socket);

    btn_link = new QPushButton(group_socket);
    btn_link->setHidden(true);

    btn_send = new QPushButton(group_socket);
    btn_send->setHidden(true);

    label_local_port = new QLabel(group_socket);

    get_msg_edit = new QTextEdit(group_get_msg);
    get_msg_edit->setHidden(true);

    send_msg_edit = new QTextEdit(group_send_msg);
    send_msg_edit->setHidden(true);

    //ctn->set_tcpclient();

}


Widget::~Widget()
{
    free_socket(ctn);       //友元函数释放socket
    free_dialog(socket_dialog);     //友元函数回收dialog_socket

    delete ctn;             //回收
    delete label_ip;
    delete label_port;
    delete btn_link;
    delete btn_send;
    delete get_msg_edit;
    delete send_msg_edit;

    //new 和delete 的顺序要对应上，因为new edit的时候是顶层窗口部件是group
    //所以在delete的时候应该先释放edit，再释放group，不然先释放group时，还没释放
    //edit，那么edit是一个野指针，然后再释放delete，释放一个野指针的后果，你应该清楚的。

    delete group_socket;
    delete group_get_msg;
    delete group_send_msg;
   // delete group_graph;
    delete ui;

}
void Widget::on_btn_tcp_client_clicked()
{

    socket_dialog = new dialog(this);

    connect(socket_dialog,&dialog::enter_tcpclient,this,&Widget::enter_tcpclient_ui);   //发出信号相应
    if(!socket_dialog->dia_tcp_client())
    {
      //  ack = false;
        return;
    }
    else{

        //注意区域的划分，是放在底层的，也就是说，代码的顺序是要放在前面的
        //区域的划分
        group_socket->setTitle(tr("Socket Message"));
        group_socket->setHidden(false);
        group_socket->setGeometry(QRect(150,10,500,80));

        group_get_msg->setTitle(tr("Recevice Message"));
        group_get_msg->setHidden(false);
        group_get_msg->setGeometry(QRect(150,100,250,160));
        group_send_msg->setTitle(tr("Send Message"));
        group_send_msg->setHidden(false);
        group_send_msg->setGeometry(QRect(400,100,250,160));
    //    group_graph->setTitle(tr("Groph"));
     //   group_graph->setHidden(false);
      //  group_graph->setGeometry(QRect(150,270,500,300));

       // qDebug()<<1;
       // qDebug()<<3;
        ctn->set_IP(socket_dialog->getIpToCtn());
        ctn->set_Port(socket_dialog->getPortToctn());
        QString ip("IP:");
        QString port("Port:");
        ip.append(ctn->getip());
        port.append(QString::number(ctn->getport()));
        //qDebug()<<port;
        //qDebug()<<ip;
        label_ip->setText(ip);
        label_port->setText(port);
        label_ip->setGeometry(QRect(10,10,100,30));
        label_port->setGeometry(QRect(110,10,100,30));

        //连接的按键定义
        btn_link->setText(tr("连接"));
        btn_link->setGeometry(QRect(250,10,80,25));
        btn_link->setHidden(false);

        btn_send->setText(tr("发送"));
        btn_send->setHidden(false);
        btn_send->setGeometry(QRect(250,40,80,25));

        //接收区域
        get_msg_edit->setGeometry(QRect(10,25,230,125));
        get_msg_edit->setHidden(false);
        //get_msg_edit->canPaste();           //使能粘贴

        send_msg_edit->setGeometry(QRect(10,25,230,125));
        send_msg_edit->setHidden(false);
        send_msg_edit->canPaste();




        //ack = true;

        connect(btn_link,&QPushButton::clicked,this,&Widget::btn_link_clicked);
        connect(btn_send,&QPushButton::clicked,this,&Widget::btn_send_clicked);
    }

}


void Widget::btn_link_clicked()
{
    qDebug()<<34;
    if(btn_link->text() == "连接")
    {
        if(!ctn->set_tcpclient())
            return ;
        else{
            ui->group_graph->setHidden(false);
            ui->tem_plot->setHidden(false);

            this->plottemp();
            connect(ctn->get_socket(),&QTcpSocket::readyRead,this,&Widget::tcp_client_ReadData);
            btn_link->setText(tr("断开"));
            QString port("LocalPort:");
            port.append(QString::number(ctn->getLocalPort()));
            label_local_port->setText(port);
            label_local_port->setGeometry(QRect(110,40,100,30));
        }
    }else if(btn_link->text() == "断开")
    {
        ctn->set_quit_tcpclient();
        btn_link->setText(tr("连接"));
    }
}

void Widget::btn_send_clicked()
{
    //qDebug()<<45;
    ctn->get_socket()->write(send_msg_edit->toPlainText().toLatin1());
    if(ctn->get_socket()->flush()) qDebug()<<00;
}


void Widget::enter_tcpclient_ui()
{

}

void Widget::tcp_client_ReadData()
{
    static int i=0;
    qDebug()<<"e";
    QByteArray buf;
    buf = ctn->get_socket()->readAll();
    if(!buf.isEmpty())          //不为空就显示
    {

        QDateTime time = QDateTime::currentDateTime();
        protocol(buf);
        if(save_intosql(time,a))qDebug()<<9;
        this->updata(i,temp_num);
        i++;
        qDebug()<<a[0]<<"  "<<a[1];
        QString str = get_msg_edit->toPlainText();
        str += buf;
        get_msg_edit->setText(str);

    }
}

void Widget::Paint()
{

}
//**************************测试
//生成随机数进行检测
void get_srand()
{
    srand(time(NULL));
    for(int i=0;i<maxlength;i++)
    {
        a[i] = random(35);
    }
    //排序  找出最大最小值
}



//向前移一位
void right_to(float *p)
{
    for(;(p+1)!=NULL;p++)
    {
        *p = *(p+1);
    }
}

bool delay()
{
    for(int i = 52440;i>0;i--){}
    for(int j = 52440;j>0;j--){}
    for(int j = 52440;j>0;j--){}
    for(int j = 52440;j>0;j--){}
    for(int j = 52440;j>0;j--){}
    return true;
}

void msecSleep1(int msec)
{
    QMutex mutex;
    QWaitCondition sleep;
    mutex.lock();
    sleep.wait(&mutex, 1000);
    mutex.unlock();
}

//阻塞
void msecSleep(int msec)
{
QTime n=QTime::currentTime();
        QTime now;
        do{
             now=QTime::currentTime();
           }while (n.msecsTo(now)<=msec);
}

//数据传输的协议。。。。。与下位机通信
void protocol(const QByteArray &buf)
{
    //可能出现的问题，读取时间的问题，和采集时间匹配上
    if(is_digits(buf.toStdString()))
    {
        a[0] = buf.toInt()/100;     //取整数部分
        a[1] = buf.toInt()%100;     //取小数部分
    }
}
//判断是否全为数字
bool is_digits(const std::string &str)
{
    return str.find_first_not_of("0123456789") == std::string::npos;
}

//储存进数据库
bool save_intosql(const QDateTime &dat,const int *ptr)
{
    //虽然不在此作用域中，但是数据库仍然着默认值
   float num = a[0] + float(a[1])/100;
   temp_num = num;
   qDebug()<<dat;
   QString s = dat.toString("yyyy-MM-dd hh:mm:ss");
   qDebug()<<s;
   qDebug()<<dat.toString("yyyy-MM-dd h:m:s")<<"  "<<num;
   QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
   QSqlQuery query(db);
   QString str = QString("insert into temperature(Data ,temperature) values('%1','%2')").arg(dat.toString("yyyy.MM.dd hh:mm:ss")).arg(num);
   if(!query.exec(str))return false;
   else return true;
}
//********************   温度折线图   *******************//

void Widget::plottemp()
{
    qDebug()<<6;
    //********************   温度折线图   *******************//
      ui->tem_plot->addGraph();                //添加一条曲线
      QPen pen;
      pen.setWidth(2);
      pen.setColor(Qt::blue);
      ui->tem_plot->graph(0)->setPen(pen);                             //设置画笔颜色
      ui->tem_plot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); //设置曲线画刷背景
      ui->tem_plot->graph(0)->setAntialiasedFill(false);

      /*ui->tem_plot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
      ui->tem_plot->xAxis->setDateTimeFormat("hh:mm:ss");*/
      //ui->tem_plot->xAxis->setAutoTickStep(false);
     // ui->tem_plot->xAxis->setTickStep(1);
      ui->tem_plot->axisRect()->setupFullAxesBox();

      ui->tem_plot->yAxis->setLabel(QStringLiteral("温度/℃"));      //设置y坐标轴名称

      ui->tem_plot->xAxis->setRange(0, 23);
      ui->tem_plot->yAxis->setRange(20, 35);

      ui->tem_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

      ui->tem_plot->graph(0)->setLineStyle((QCPGraph::LineStyle)1);
      ui->tem_plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));

      //ui->tem_plot->legend->setVisible(true);
      //ui->tem_plot->legend->setFont(QFont(QStringLiteral("新蒂下午茶白金版"),11));
      ui->tem_plot->xAxis->setTickLabelFont(QFont(QStringLiteral("新蒂下午茶白金版"),11));
      ui->tem_plot->yAxis->setTickLabelFont(QFont(QStringLiteral("新蒂下午茶白金版"),11));
      ui->tem_plot->xAxis->setLabelFont(QFont(QStringLiteral("新蒂下午茶白金版"),12));
      ui->tem_plot->yAxis->setLabelFont(QFont(QStringLiteral("新蒂下午茶白金版"),12));
      //ui->tem_plot->graph(0)->setScatterStyle(QCPScatterStyle(customScatterPath, QPen(), QColor(40, 70, 255, 50), 10));

      connect(ui->tem_plot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->tem_plot->xAxis2, SLOT(setRange(QCPRange)));
      connect(ui->tem_plot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->tem_plot->yAxis2, SLOT(setRange(QCPRange)));
      ui->tem_plot->replot();
}
void Widget::updata(const int i,const float dat)
{
    ui->tem_plot->graph(0)->addData(i, dat);
    qDebug()<<2;
    if(dat >= 24)
    {
      ui->tem_plot->xAxis->setRange(i-23, i);
    }
    ui->tem_plot->replot();
}
//********************中文乱码还未更正
//********************类间关系还未明了，如果还增加几个连接关系就不能成功了
//********************对方断开连接后，我方按键未响应

