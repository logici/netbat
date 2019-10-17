#ifndef DIALOG_H
#define DIALOG_H
//#include "widget.h"
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QObject>


class dialog:public QDialog
{
    Q_OBJECT
public:
    explicit dialog(QWidget *parent = 0);
    ~dialog();
    bool dia_tcp_client();
    QString getIpToCtn()const;
    unsigned int getPortToctn()const;

    friend void free_dialog(dialog *d);

    QPushButton *btn_ok;
    QPushButton *btn_cel;
private:
    QDialog *dia;
    QLabel *label_IP;
    QLabel *label_Port;
    QLineEdit *IP_edit;
    QLineEdit *Port_edit;

    QString getip;
    unsigned int getport;

    //槽函数
public slots:
    void get_IP();

signals:
    enter_tcpclient();
    void getok();
};

#endif // DIALOG_H
