#include "balancing_programm.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	balancing_programm w;
	w.show();
	return a.exec();
}
