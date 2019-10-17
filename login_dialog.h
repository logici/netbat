#ifndef LOGIN_DIALOG_H
#define LOGIN_DIALOG_H
#include <QDialog>

//作用域？？？？Ui？？？？？
namespace Ui{
class login_dialog;
}

class login_dialog:public QDialog
{
    Q_OBJECT                //宏定义？？？？？
public:
    explicit login_dialog(QWidget *parent = 0);
    ~login_dialog();
private :
    Ui::login_dialog *login_dia;


private slots:
    void on_loginBtn_clicked();
    void on_logonBtn_clicked();
};

#endif // LOGIN_DIALOG_H
