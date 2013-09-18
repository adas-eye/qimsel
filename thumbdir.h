#ifndef THUMBDIR_H
#define THUMBDIR_H

#include <QObject>
#include <QDir>
#include <QListWidgetItem>
#include <QMimeDatabase>
#include <QDBusInterface>

class ThumbDir : public QObject
{
	Q_OBJECT

public:
	ThumbDir(const QDir &dir = QDir::home());

signals:
	void pathCopied();
	void dirChanged(QList<QListWidgetItem *> newItems);

public slots:
	void followItem(QListWidgetItem *item);

protected:
	static const QString DBusService;
	static const QString DBusPath;
	static QMimeDatabase MimeDatabase;
	static QStringList *SupportedImageTypes;

	static const QStringList &supportedImageTypes();

	QDir dir;
	QDBusInterface iface;
	unsigned int currentHandle;
	QList<QListWidgetItem *> currentItems;

	void fillItems();
	void request(const QFileInfoList &files);

protected slots:
	void completeRequest(unsigned int handle, QStringList URIs);

};

#endif // THUMBDIR_H
 
// vim: set ts=4 sw=4 noet:
