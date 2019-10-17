#include "login_dialog.h"
#include "widget.h"
#include "sql_connnect.h"
#include "connection.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if(!create_sqlconnection())return 0;
    Widget w;
    login_dialog log_dia;
    if(log_dia.exec() == QDialog::Accepted)
    {
        w.show();
        return a.exec();
    }
    else return 0;
}
