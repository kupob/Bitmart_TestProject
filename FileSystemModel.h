#ifndef FILESYSTEMMODEL_H
#define FILESYSTEMMODEL_H

#include <QFileSystemModel>

class FileSystemModel : public QFileSystemModel
{
public:
    FileSystemModel(QObject* parent = Q_NULLPTR);

    int columnCount(const QModelIndex &parent) const;
};

#endif // FILESYSTEMMODEL_H
