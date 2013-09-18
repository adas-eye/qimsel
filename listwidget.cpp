#include "listwidget.h"

#include <QApplication>
#include <QKeyEvent>

const int ListWidget::ZoomStep = 16;

ListWidget::ListWidget(QWidget *parent) :
	QListWidget(parent)
{
	this->setViewMode(QListWidget::IconMode);
	connect(this, SIGNAL(itemActivated(QListWidgetItem *)),
			&thumbDir, SLOT(followItem(QListWidgetItem *)));
	connect(&thumbDir, SIGNAL(dirChanged(QList<QListWidgetItem *>)),
			this, SLOT(addAll(QList<QListWidgetItem *>)));

	QListWidgetItem i(".");
	thumbDir.followItem(&i);
}

void ListWidget::keyPressEvent(QKeyEvent *e)
{
	// TODO n searches name
	switch (e->key()) {
	case Qt::Key_I:
		zoom(ZoomStep);
		break;
	case Qt::Key_O:
		zoom(-ZoomStep);
		break;
	case Qt::Key_B:
		thumbDir.followItem(this->item(0));
		break;
	case Qt::Key_F:
		sendKeyPress(e, Qt::Key_Return);
		break;
	case Qt::Key_H:
		sendKeyPress(e, Qt::Key_Left);
		break;
	case Qt::Key_J:
		sendKeyPress(e, Qt::Key_Down);
		break;
	case Qt::Key_K:
		sendKeyPress(e, Qt::Key_Up);
		break;
	case Qt::Key_L:
		sendKeyPress(e, Qt::Key_Right);
		break;
	default:
		QListWidget::keyPressEvent(e);
	}
}

void ListWidget::sendKeyPress(QKeyEvent *e, int key)
{
	QApplication::postEvent(this,
			new QKeyEvent(QEvent::KeyPress, key, e->modifiers()));
}

void ListWidget::zoom(int pixels)
{
	QSize zoom(pixels, pixels);
	setIconSize(iconSize() + zoom);
	setGridSize(gridSize() + zoom);
}

void ListWidget::addAll(const QList<QListWidgetItem *> &items)
{
	clear();

	foreach(QListWidgetItem *i, items)
		addItem(i);

	setCurrentRow(0);
}

// vim: set ts=4 sw=4 noet:
