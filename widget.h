#ifndef WIDGET_H
#define WIDGET_H
#include <QtGui>             //控件
#include <QPaintEvent>      //绘画事件
#include <QWidget>
#include <QGroupBox>
#include <QTextEdit>
#include "qcustomplot.h"
#include "connection.h"
#include "dialog.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void Paint();
    void Paint_point(int *);
    void plottemp();
    void updata(const int i,const float dat);
private slots:
    void on_btn_tcp_client_clicked();
    void enter_tcpclient_ui();
    void btn_link_clicked();
    void btn_send_clicked();
    void tcp_client_ReadData();
private:
    Ui::Widget *ui;         //ui界面
    QImage image;           //绘图画布
    connection *ctn ;       //tcp连接
    dialog *socket_dialog;

    QLabel *label_ip;
    QLabel *label_port;
    QPushButton *btn_link;
    QPushButton *btn_send;
    QLabel *label_local_port;
    QGroupBox *group_socket;
    QGroupBox *group_get_msg;
    QGroupBox *group_send_msg;
   // QGroupBox *group_graph;
    QTextEdit *get_msg_edit;
    QTextEdit *send_msg_edit;
//signals:
    //void enter_tcpclient();

protected:
    void paintEvent(QPaintEvent *)
    {
        QPainter painter(this);
        painter.drawImage(150,290,image);
    }

};

#endif // WIDGET_H
