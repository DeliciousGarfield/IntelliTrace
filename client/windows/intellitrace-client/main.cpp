#include <QApplication>
#include "tracer.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setQuitOnLastWindowClosed(false);

	Tracer* tracer = Tracer::getInstance();
	tracer->createUI();
	tracer->startUp();
	tracer->enableLog();

	return a.exec();
}
