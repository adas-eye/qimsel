#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
	Q_OBJECT
public:
	explicit Dialog(QWidget *parent = 0);
	virtual ~Dialog();

private:
	Ui::Dialog *ui;
};

#endif // DIALOG_H

// vim: set ts=4 sw=4 noet:
