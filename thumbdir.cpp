#include "thumbdir.h"

#include <QImageReader>
#include <QFileInfo>
#include <QApplication>
#include <QClipboard>
#include <QDBusReply>
#include <QFileInfo>
#include <QCryptographicHash>

const QString ThumbDir::DBusService = "org.freedesktop.thumbnails.Thumbnailer1";

const QString ThumbDir::DBusPath = "/org/freedesktop/thumbnails/Thumbnailer1";

QMimeDatabase ThumbDir::MimeDatabase;

QStringList *ThumbDir::SupportedImageTypes = 0;

const QStringList &ThumbDir::supportedImageTypes()
{
	if (!SupportedImageTypes) {
		SupportedImageTypes = new QStringList;
		QList<QByteArray> exts = QImageReader::supportedImageFormats();
		foreach (QByteArray a, exts)
			(*SupportedImageTypes) << "*." + a.toLower();
	}
	return *SupportedImageTypes;
}

ThumbDir::ThumbDir(const QDir &dir) :
	dir(dir),
	iface(DBusService, DBusPath)
{
	QDBusConnection::sessionBus().connect(DBusService, DBusPath, QString(),
			"Ready", this, SLOT(completeRequest(unsigned int, QStringList)));
}

void ThumbDir::followItem(QListWidgetItem *item)
{
	QFileInfo file(dir.absolutePath(), item->text());
	if (!file.exists() || !file.isReadable())
		return;

	if (file.isDir() && dir.cd(file.fileName())) {
		fillItems();
	} else {
		QApplication::clipboard()->setText(file.absoluteFilePath());
		emit pathCopied();
	}
}

void ThumbDir::fillItems()
{
	currentItems.clear();

	QFileInfoList dirs = dir.entryInfoList(
			QDir::Dirs | QDir::Hidden | QDir::NoDot);
	foreach (QFileInfo d, dirs)
		currentItems << new QListWidgetItem(
				QIcon::fromTheme("folder"), d.fileName());

	QFileInfoList images = dir.entryInfoList(
			supportedImageTypes(), QDir::Files | QDir::Hidden);
	request(images);
}

void ThumbDir::request(const QFileInfoList &files)
{
	QStringList URIs;
	QStringList mimes;

	foreach (QFileInfo f, files) {
		QString path = f.absoluteFilePath();
		URIs << "file://" + path;
		mimes << MimeDatabase.mimeTypeForFile(path).name();
	}

	QDBusReply<unsigned int> handle =
		iface.call("Queue", URIs, mimes, "normal", "default", (unsigned int)0);
	currentHandle = handle.value();
}

void ThumbDir::completeRequest(unsigned int handle, QStringList URIs)
{
	if (handle != currentHandle)
		return;

	foreach(QString f, URIs) {
		QString fileName = QCryptographicHash::hash(f.toUtf8(), QCryptographicHash::Md5).toHex();
		QString path = QDir::homePath() + QDir::separator() +
			".thumbnails" + QDir::separator() +
			"normal" + QDir::separator() +
			fileName + ".png";
		currentItems << new QListWidgetItem(QIcon(path), QFileInfo(f).fileName());
	}

	emit dirChanged(currentItems);
}

// vim: set ts=4 sw=4 noet:
