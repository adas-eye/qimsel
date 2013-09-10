#ifndef THUMBWIDGET_H
#define THUMBWIDGET_H

#include <QListWidget>

#include "dir.h"

class ThumbWidget : public QListWidget
{
	Q_OBJECT
public:
	explicit ThumbWidget(QWidget *parent = 0,
			const QString &dirPath = QDir::homePath());
	virtual ~ThumbWidget();

protected:
	static const int ZoomStep;
	static QStringList ImageFilters;

	static const QStringList &imageFilters();

	Dir dir;

	void keyPressEvent(QKeyEvent *e);
	void sendKeyPress(QKeyEvent *e, int key);
	void zoom(int pixels);

protected slots:
	void follow(QListWidgetItem *item);
	void fill();
};

#endif // THUMBWIDGET_H

/* vim: set ts=4 sw=4 noet: */
