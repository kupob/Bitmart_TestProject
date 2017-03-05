#include "ThumbnailsView.h"

#include <QWheelEvent>

ThumbnailsView::ThumbnailsView(QWidget *parent) :
    QListView(parent)
{

}

void ThumbnailsView::wheelEvent(QWheelEvent *event)
{
    if (event->angleDelta().y() < 0)
        emit mouseWheeledDown();
    else
        emit mouseWheeledUp();

    emit itemDelegate()->sizeHintChanged(QModelIndex());

    event->accept();
}
