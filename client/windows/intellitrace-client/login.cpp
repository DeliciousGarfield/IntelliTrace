#include <QtGui>
#include "login.h"

LoginDialog::LoginDialog(QWidget *parent) : QDialog(parent)
{
	setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
	setupUi(this);
}