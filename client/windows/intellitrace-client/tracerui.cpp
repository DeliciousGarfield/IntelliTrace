#include "tracerui.h"

TracerUI::TracerUI()
{
	loginDialog = new LoginDialog;
	statusDialog = new StatusDialog;
}

void TracerUI::setupUI()
{
	createActions();
	createTrayIcon();
}

void TracerUI::createTrayIcon()
{
	trayIconMenu = new QMenu(NULL);
	trayIconMenu->addAction(loginAction);
	trayIconMenu->addAction(statusAction);
	trayIconMenu->addSeparator();
	trayIconMenu->addAction(quitAction);

	trayIcon = new QSystemTrayIcon(QIcon(":/images/app.png"));
	trayIcon->setContextMenu(trayIconMenu);
	trayIcon->show();
	trayIcon->showMessage(QString("intellitrace"), QString("Client is running."));
}

void TracerUI::createActions()
{
	loginAction = new QAction(("&Login"), NULL);
	connect(loginAction, SIGNAL(triggered()), this, SLOT(login()));

	statusAction = new QAction(("&Status"), NULL);
	connect(statusAction, SIGNAL(triggered()), this, SLOT(status()));

	viewAction = new QAction(("&View"), NULL);
	//connect(viewAction, SIGNAL(triggered()), this, SLOT(view()));

	quitAction = new QAction(("&Quit"), NULL);
	connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void TracerUI::login()
{
	loginDialog->show();
}

void TracerUI::status()
{
	statusDialog->show();
}

void TracerUI::log(QString info)
{
	QTextEdit *logger = statusDialog->textHistory;
	logger->append(info);
}