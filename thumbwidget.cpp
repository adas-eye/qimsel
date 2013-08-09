#include "thumbwidget.h"

#include <QImageReader>
#include <QApplication>
#include <QClipboard>
#include <QKeyEvent>

ThumbWidget::ThumbWidget(QWidget *parent, const QString &dirPath) :
    QListWidget(parent),
    dir(dirPath)
{
    this->setViewMode(QListWidget::IconMode);
    connect(this, SIGNAL(itemActivated(QListWidgetItem *)),
            SLOT(follow(QListWidgetItem *)));
    connect(&dir, SIGNAL(dirChanged()),
            SLOT(fill()));
    fill();
}

ThumbWidget::~ThumbWidget()
{
}

const int ThumbWidget::ZoomStep = 16;

QStringList ThumbWidget::ImageFilters;

const QStringList &ThumbWidget::imageFilters()
{
    if (ImageFilters.isEmpty()) {
        QList<QByteArray> extensions = QImageReader::supportedImageFormats();
        for (QList<QByteArray>::const_iterator i = extensions.begin();
             i != extensions.end(); ++i)
            ImageFilters << "*." + (*i).toLower();
    }
    return ImageFilters;
}

void ThumbWidget::keyPressEvent(QKeyEvent *e)
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
        dir.cdUp();
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

void ThumbWidget::sendKeyPress(QKeyEvent *e, int key)
{
    QApplication::postEvent(this,
            new QKeyEvent(QEvent::KeyPress, key, e->modifiers()));
}

void ThumbWidget::zoom(int pixels)
{
    QSize zoom(pixels, pixels);
    setIconSize(iconSize() + zoom);
    setGridSize(gridSize() + zoom);
}

void ThumbWidget::follow(QListWidgetItem *item)
{
    QString file = item->text();
    QFileInfo fileInfo(dir.qDir().absolutePath(), file);
    if (!fileInfo.exists() || !fileInfo.isReadable())
        return;
    if (fileInfo.isDir()) {
        dir.cd(file);
    } else {
        QApplication::clipboard()->setText(dir.qDir().absoluteFilePath(file));
        // TODO quit as a command-line parameter
    }
}

void ThumbWidget::fill()
{
    clear();

    QFileInfoList dirs = dir.qDir().entryInfoList(
                QDir::Dirs | QDir::Hidden | QDir::NoDotAndDotDot);
    QFileInfoList images = dir.qDir().entryInfoList(
                imageFilters(), QDir::Files | QDir::Hidden);

    for (QFileInfoList::const_iterator i = dirs.begin();
         i != dirs.end(); ++i)
        new QListWidgetItem(QIcon::fromTheme("folder"),
                            (*i).fileName(), this);

    for (QFileInfoList::const_iterator i = images.begin();
         i != images.end(); ++i)
        new QListWidgetItem(QIcon((*i).absoluteFilePath()),
                            (*i).fileName(), this);

    setCurrentRow(0);
}
