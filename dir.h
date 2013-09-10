#ifndef DIR_H
#define DIR_H

#include <QDir>

class Dir : public QObject
{
	Q_OBJECT
public:
	explicit Dir(const QString &path);
	virtual ~Dir();

	const QDir &qDir() const;
	bool cd(const QString &dirName);
	bool cdUp();

private:
	QDir dir;

signals:
	void dirChanged();
};

#endif // DIR_H

/* vim: set ts=4 sw=4 noet: */
