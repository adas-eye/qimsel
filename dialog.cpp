#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Dialog)
{
	ui->setupUi(this);
	ui->listWidget->setFocus();
}

Dialog::~Dialog()
{
	delete ui;
}

/* vim: set ts=4 sw=4 noet: */
