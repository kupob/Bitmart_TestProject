#ifndef THUMBNAILSLOADERTHREAD_H
#define THUMBNAILSLOADERTHREAD_H

#include <QThread>
#include <QIcon>

class ThumbnailsLoaderThread : public QThread
{
    Q_OBJECT

public:
    ThumbnailsLoaderThread (QObject *parent = Q_NULLPTR);

    void setDirPath(const QString& dirPath);

    void run();

signals:
    void pixmapCalculated(const QPixmap& pixmap);

private:
    QString _dirPath;
};

#endif // THUMBNAILSLOADERTHREAD_H
