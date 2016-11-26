#pragma once

#include <QDialog>
#include "ui_status.h"

class StatusDialog : public QDialog, public Ui::StatusDialog
{
	Q_OBJECT
public:
	StatusDialog(QWidget *parent = 0);
};