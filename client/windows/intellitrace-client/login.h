#pragma once

#include <QDialog>
#include "ui_login.h"

class LoginDialog : public QDialog, public Ui::LoginDialog
{
	Q_OBJECT
public:
	LoginDialog(QWidget *parent = 0);
};