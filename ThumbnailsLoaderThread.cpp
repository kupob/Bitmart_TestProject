#include "ThumbnailsLoaderThread.h"

#include <QDir>
#include <QPixmap>
#include <QPainter>

#include "common.h"

ThumbnailsLoaderThread::ThumbnailsLoaderThread(QObject *parent) :
    QThread(parent)
{

}

void ThumbnailsLoaderThread::setDirPath(const QString &dirPath)
{
    _dirPath = dirPath;
}

void ThumbnailsLoaderThread::run()
{
    if (_dirPath.isEmpty())
    {
        return;
    }

    QDir dir(_dirPath);
    QStringList fileList = dir.entryList(QStringList() << "*.*");
    foreach (QString fileName, fileList)
    {
        QPixmap fileImage(_dirPath + "/" + fileName);
        if (!fileImage.isNull())
        {
            int xIndent, yIndent;   // отступы по координатам при рисовании
            int newWidth, newHeight;    // новая ширина и высота картинки внутри квадрата
            int maxCoord = qMax(fileImage.width(), fileImage.height());
            newWidth = fileImage.width() * thumbMaximumSize / maxCoord;
            newHeight = fileImage.height() * thumbMaximumSize / maxCoord;

            xIndent = (thumbMaximumSize - newWidth) / 2;
            yIndent = (thumbMaximumSize - newHeight) / 2;

            QPixmap thumbnail(thumbMaximumSize, thumbMaximumSize);
            thumbnail.fill(Qt::transparent);
            QPainter p;
            p.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
            p.begin(&thumbnail);
            p.drawPixmap(xIndent, yIndent, thumbMaximumSize - 2 * xIndent, thumbMaximumSize - 2 * yIndent, fileImage);
            p.end();

            emit pixmapCalculated(thumbnail);
        }
    }
}
