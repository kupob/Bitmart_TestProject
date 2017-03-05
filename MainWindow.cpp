#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "FileSystemModel.h"
#include "ThumbnailsViewModel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _fileSystemModel = QSharedPointer<FileSystemModel>(new FileSystemModel(this));
    _fileSystemModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    _fileSystemModel->setRootPath(QDir::currentPath());
    ui->fileSystemView->setModel(_fileSystemModel.data());

    _thumbnailsModel = QSharedPointer<ThumbnailsViewModel>(new ThumbnailsViewModel(this));
    ui->thumbnailsView->setViewMode(QListView::IconMode);
    ui->thumbnailsView->setResizeMode(QListView::Adjust);
    ui->thumbnailsView->setModel(_thumbnailsModel.data());

    ui->splitter->setStretchFactor(0, 1);
    ui->splitter->setStretchFactor(1, 3);

    connect(ui->fileSystemView, &QTreeView::clicked, this, &MainWindow::loadThumbnails);

    connect(ui->thumbnailsView, &ThumbnailsView::mouseWheeledDown,
            _thumbnailsModel.data(), &ThumbnailsViewModel::zoomOut);
    connect(ui->thumbnailsView, &ThumbnailsView::mouseWheeledUp,
            _thumbnailsModel.data(), &ThumbnailsViewModel::zoomIn);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadThumbnails(const QModelIndex &index)
{
    QFileInfo fileInfo = _fileSystemModel->fileInfo(index);
    _thumbnailsModel->setCurrentDir(fileInfo.absoluteFilePath());
}
