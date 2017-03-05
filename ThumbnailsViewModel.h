#ifndef THUMBNAILSVIEWMODEL_H
#define THUMBNAILSVIEWMODEL_H

#include <QAbstractListModel>
#include <QIcon>

class ThumbnailsViewModel : public QAbstractListModel
{
    Q_OBJECT

public:
    ThumbnailsViewModel(QObject* parent = Q_NULLPTR);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data (const QModelIndex &index, int role = Qt::DisplayRole) const;

public slots:
    void setCurrentDir(const QString& dirPath);
    void addPixmap(const QPixmap &pixmap);

    void zoomIn();
    void zoomOut();

private:
    QString _dirPath;

    QVector<QPixmap> _data;
    int _thumbCurrentSize;
};

#endif // THUMBNAILSVIEWMODEL_H
