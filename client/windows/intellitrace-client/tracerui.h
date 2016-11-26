#ifndef TRACERUI_H
#define TRACERUI_H

#include <QSystemTrayIcon>
#include <QAction>
#include <QMenu>

#include "login.h"
#include "status.h"

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
QT_END_NAMESPACE

class TracerUI : public QObject
{
	Q_OBJECT
public:
	TracerUI();
	void setupUI();
	void createTrayIcon();
	void createActions();
	private slots:
	void login();
	void status();
private:
	QAction *loginAction;
	QAction *statusAction;
	QAction *viewAction;
	QAction *quitAction;

	QSystemTrayIcon *trayIcon;
	QMenu *trayIconMenu;

	LoginDialog *loginDialog;
	StatusDialog *statusDialog;
public slots:
	void log(QString info);
};

#endif // TRACERUI_H
