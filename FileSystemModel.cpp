#include "FileSystemModel.h"

FileSystemModel::FileSystemModel(QObject *parent) :
    QFileSystemModel(parent)
{

}

int FileSystemModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}
