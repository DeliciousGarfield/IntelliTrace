#include <QtGui>
#include "status.h"

StatusDialog::StatusDialog(QWidget *parent) : QDialog(parent)
{
	setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
	setupUi(this);
}