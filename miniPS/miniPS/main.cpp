#include "miniPS.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	miniPS w;
	w.show();
	return a.exec();
}
