#pragma once

#include <QListWidget>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDropEvent>
#include <QDragMoveEvent>
#include <QUrl>
#include "PlayListDTOs.hpp"

struct DropIndicatorLine {
    bool active = false;
    QPointF beginningPoint;
    qreal width;
};

class PlayListWidget : public QListWidget {
    Q_OBJECT
     public:
        explicit PlayListWidget(QWidget *parent = nullptr);
        void addPlayListItem(const PlayListItem & playListItem, int rowIndex = -1);

     signals:
        void fileDropped(QUrl fileUrl, int droppedIndex);
        void filesDropped(QList<QUrl> filesUrl, int droppedIndex);

     protected:
        void dragEnterEvent(QDragEnterEvent *event);
        void dragLeaveEvent(QDragLeaveEvent *event);
        void dropEvent(QDropEvent *e);
        void dragMoveEvent(QDragMoveEvent *e);
        void paintEvent(QPaintEvent *event);
        DropIndicatorLine dropIndicatorLine;
        QPointF getDropIndicatorPosition(const QPointF &mousePosition);
        int getDroppingItemIndex(const QPointF &mousePosition);
        static bool isDropIndicatorOnTopOrBottom(const QRect &itemRectangle, const QPointF &mousePosition);
};
