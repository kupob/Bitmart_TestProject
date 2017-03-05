#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSharedPointer>

class FileSystemModel;
class ThumbnailsViewModel;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void loadThumbnails(const QModelIndex& index);

private:
    Ui::MainWindow *ui;
    QSharedPointer<FileSystemModel> _fileSystemModel;
    QSharedPointer<ThumbnailsViewModel> _thumbnailsModel;

    QString _currentDir;
};

#endif // MAINWINDOW_H
