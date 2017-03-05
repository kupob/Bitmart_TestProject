#ifndef THUMBNAILSVIEW_H
#define THUMBNAILSVIEW_H

#include <QListView>

class ThumbnailsView : public QListView
{
    Q_OBJECT

public:
    ThumbnailsView(QWidget *parent = Q_NULLPTR);

    void wheelEvent(QWheelEvent *event);

signals:
    void mouseWheeledDown();
    void mouseWheeledUp();
};

#endif // THUMBNAILSVIEW_H
