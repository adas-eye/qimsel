#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QListWidget>
#include "thumbdir.h"

class ListWidget : public QListWidget
{
	Q_OBJECT
public:
	ListWidget(QWidget *parent = 0);

protected:
	static const int ZoomStep;

	ThumbDir thumbDir;

	void keyPressEvent(QKeyEvent *e);
	void sendKeyPress(QKeyEvent *e, int key);
	void zoom(int pixels);

protected slots:
	void addAll(const QList<QListWidgetItem *> &items);
};

#endif // LISTWIDGET_H

// vim: set ts=4 sw=4 noet:
