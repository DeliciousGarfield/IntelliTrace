/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

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

class Ui_LoginDialog
{
public:
    QPushButton *btnLogin;
    QPushButton *btnRegister;
    QLineEdit *textUsername;
    QLineEdit *textPassword;
    QLabel *labelUsername;
    QLabel *labelPassword;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName(QStringLiteral("LoginDialog"));
        LoginDialog->resize(450, 280);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/app.png"), QSize(), QIcon::Normal, QIcon::Off);
        LoginDialog->setWindowIcon(icon);
        btnLogin = new QPushButton(LoginDialog);
        btnLogin->setObjectName(QStringLiteral("btnLogin"));
        btnLogin->setGeometry(QRect(140, 210, 93, 28));
        btnRegister = new QPushButton(LoginDialog);
        btnRegister->setObjectName(QStringLiteral("btnRegister"));
        btnRegister->setGeometry(QRect(260, 210, 93, 28));
        textUsername = new QLineEdit(LoginDialog);
        textUsername->setObjectName(QStringLiteral("textUsername"));
        textUsername->setGeometry(QRect(140, 70, 211, 31));
        textPassword = new QLineEdit(LoginDialog);
        textPassword->setObjectName(QStringLiteral("textPassword"));
        textPassword->setGeometry(QRect(140, 130, 211, 31));
        labelUsername = new QLabel(LoginDialog);
        labelUsername->setObjectName(QStringLiteral("labelUsername"));
        labelUsername->setGeometry(QRect(40, 70, 72, 21));
        labelPassword = new QLabel(LoginDialog);
        labelPassword->setObjectName(QStringLiteral("labelPassword"));
        labelPassword->setGeometry(QRect(40, 130, 72, 21));
#ifndef QT_NO_SHORTCUT
        labelUsername->setBuddy(textUsername);
        labelPassword->setBuddy(textPassword);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(textUsername, textPassword);
        QWidget::setTabOrder(textPassword, btnLogin);
        QWidget::setTabOrder(btnLogin, btnRegister);

        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QApplication::translate("LoginDialog", "Intellitrace", 0));
        btnLogin->setText(QApplication::translate("LoginDialog", "Login", 0));
        btnRegister->setText(QApplication::translate("LoginDialog", "Register", 0));
        labelUsername->setText(QApplication::translate("LoginDialog", "Username", 0));
        labelPassword->setText(QApplication::translate("LoginDialog", "Password", 0));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
