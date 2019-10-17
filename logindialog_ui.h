#ifndef LOGINDIALOG_UI_H
#define LOGINDIALOG_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE
class logindialog_ui
{
public:
    QLabel *label_2;
    QLineEdit *usrLineEdit;
    QPushButton *loginBtn;
    QPushButton *logonBtn;
    QLabel *label;
    QLineEdit *pwdLineEdit;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName(QStringLiteral("LoginDialog"));
        LoginDialog->resize(400, 300);
        label_2 = new QLabel(LoginDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(51, 81, 36, 16));
        usrLineEdit = new QLineEdit(LoginDialog);
        usrLineEdit->setObjectName(QStringLiteral("usrLineEdit"));
        usrLineEdit->setGeometry(QRect(95, 24, 131, 20));
        loginBtn = new QPushButton(LoginDialog);
        loginBtn->setObjectName(QStringLiteral("loginBtn"));
        loginBtn->setGeometry(QRect(60, 200, 75, 23));
        logonBtn = new QPushButton(LoginDialog);
        logonBtn->setObjectName(QStringLiteral("logonBtn"));
        logonBtn->setGeometry(QRect(170, 200, 75, 23));
        label = new QLabel(LoginDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(41, 24, 48, 16));
        pwdLineEdit = new QLineEdit(LoginDialog);
        pwdLineEdit->setObjectName(QStringLiteral("pwdLineEdit"));
        pwdLineEdit->setGeometry(QRect(95, 81, 131, 20));
        pwdLineEdit->setEchoMode(QLineEdit::Password);
        label->raise();
        label_2->raise();
        usrLineEdit->raise();
        loginBtn->raise();
        logonBtn->raise();
        label->raise();
        label_2->raise();
        label->raise();
        usrLineEdit->raise();
        label_2->raise();
        pwdLineEdit->raise();

        retranslateUi(LoginDialog);
        //QObject::connect(exitBtn, SIGNAL(clicked()), LoginDialog, SLOT(close()));
        //遍历名字是 on_<实例名>_<信号名>的槽函数
        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QApplication::translate("LoginDialog", "Dialog", 0));
        label_2->setText(QApplication::translate("LoginDialog", "\345\257\206\347\240\201\357\274\232", 0));
        usrLineEdit->setPlaceholderText(QApplication::translate("LoginDialog", "\350\257\267\350\276\223\345\205\245\344\275\240\347\232\204\347\224\250\346\210\267\345\220\215", 0));
        loginBtn->setText(QApplication::translate("LoginDialog", "\347\231\273\351\231\206", 0));
        logonBtn->setText(QApplication::translate("LoginDialog", "\346\263\250\345\206\214", 0));
        label->setText(QApplication::translate("LoginDialog", "\347\224\250\346\210\267\345\220\215\357\274\232", 0));
        pwdLineEdit->setPlaceholderText(QApplication::translate("LoginDialog", "\350\257\267\350\276\223\345\205\245\345\257\206\347\240\201", 0));
    } // retranslateUi
};
namespace Ui {
    class login_dialog: public logindialog_ui {};
} // namespace Ui
QT_END_NAMESPACE
#endif // LOGINDIALOG_UI_H
