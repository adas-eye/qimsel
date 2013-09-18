#include <QApplication>

#include "dialog.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Dialog d;
	d.show();

	return a.exec();
}

// vim: set ts=4 sw=4 noet:
