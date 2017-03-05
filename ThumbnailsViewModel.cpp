#include "ThumbnailsViewModel.h"

#include "ThumbnailsLoaderThread.h"
#include "common.h"

ThumbnailsViewModel::ThumbnailsViewModel(QObject *parent) :
    QAbstractListModel(parent) ,
    _thumbCurrentSize (thumbMaximumSize)
{

}

int ThumbnailsViewModel::rowCount(const QModelIndex &parent) const
{
    return _data.count();
}

QVariant ThumbnailsViewModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() > _data.count())
        return QVariant();

    switch (role) {
    case Qt::DecorationRole:
    {
        if (_thumbCurrentSize == thumbMaximumSize)
            return _data.value(index.row());
        else
            return _data.value(index.row()).scaled(_thumbCurrentSize,
                                                   _thumbCurrentSize);
    }
    default:
        return QVariant();
    }
}

void ThumbnailsViewModel::setCurrentDir(const QString &dirPath)
{
    beginResetModel();

    _dirPath = dirPath;
    _data.clear();

    endResetModel();

    ThumbnailsLoaderThread *loaderThread = new ThumbnailsLoaderThread(this);
    loaderThread->setDirPath(dirPath);
    connect(loaderThread, &ThumbnailsLoaderThread::pixmapCalculated, this, &ThumbnailsViewModel::addPixmap);
    connect(loaderThread, &ThumbnailsLoaderThread::finished, loaderThread, &QObject::deleteLater);
    loaderThread->start();
}

void ThumbnailsViewModel::addPixmap(const QPixmap &pixmap)
{
    beginInsertRows(QModelIndex(), _data.count(), _data.count());

    _data << pixmap;

    endInsertRows();
}

void ThumbnailsViewModel::zoomIn()
{
    int newSize = qMin(thumbMaximumSize, _thumbCurrentSize + thumbSingleStep);

    if (newSize != _thumbCurrentSize)
    {
        _thumbCurrentSize = newSize;
        emit dataChanged(index(0), index(_data.count() - 1));
    }
}

void ThumbnailsViewModel::zoomOut()
{
    int newSize = qMax(thumbMinimumSize, _thumbCurrentSize - thumbSingleStep);

    if (newSize != _thumbCurrentSize)
    {
        _thumbCurrentSize = newSize;
        emit dataChanged(index(0), index(_data.count() - 1));
    }
}
