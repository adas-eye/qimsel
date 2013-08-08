#include "dir.h"

Dir::Dir(const QString &path)
    : dir(path)
{
}

Dir::~Dir()
{
}

const QDir &Dir::qDir() const
{
    return dir;
}

bool Dir::cd(const QString &dirName)
{
    if (!dir.cd(dirName))
        return false;
    emit dirChanged();
    return true;
}

bool Dir::cdUp()
{
    if (!dir.cdUp())
        return false;
    emit dirChanged();
    return true;
}
