#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Dialog w;
	w.show();
	return a.exec();
}

/* vim: set ts=4 sw=4 noet: */
