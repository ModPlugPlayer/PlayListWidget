#include <QMimeData>
#include <QPainter>
#include "PlayListWidget.hpp"
#include "PlayListItemWidget.hpp"

PlayListWidget::PlayListWidget(QWidget *parent)
    : QListWidget(parent)
{
    setAcceptDrops(true);
    QListWidget::setDropIndicatorShown(false);
}

void PlayListWidget::addPlayListItem(const PlayListItem & playListItem, int rowIndex)
{
    if(rowIndex == -1)
        rowIndex = count();
    qDebug()<<"RowIndex:"<<rowIndex;
    QListWidgetItem *item = new QListWidgetItem(this);
    PlayListItemWidget *playlistItemWidget = new PlayListItemWidget(this, playListItem);
    //playlistItemWidget->setItemNumber(rowIndex);
    item->setSizeHint(playlistItemWidget->minimumSizeHint());

    setItemWidget(item, playlistItemWidget);

    /*
    if(rowIndex == count())
        addItem(item);
    else*/
    insertItem(rowIndex, item);
}

void PlayListWidget::dragEnterEvent(QDragEnterEvent * event)
{

    /*
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
        return;
    }

    if ( event->source() != this ) {
        setDragDropMode ( QAbstractItemView::DragDrop );
    } else {
        setDragDropMode (QAbstractItemView::InternalMove);
    }
    event->acceptProposedAction();
*/
    dropIndicatorLine.active = true;
    viewport()->update();
    QListWidget::dragEnterEvent(event);
    event->acceptProposedAction();
}

void PlayListWidget::dragLeaveEvent(QDragLeaveEvent * event)
{
    dropIndicatorLine.active = false;
    viewport()->update();
    QListWidget::dragLeaveEvent(event);
    event->accept();
}

void PlayListWidget::dropEvent(QDropEvent * event)
{
    dropIndicatorLine.active = false;
    viewport()->update();
    if (event->mimeData()->hasUrls()) {
        QList<QUrl> urls = event->mimeData()->urls();
        if(urls.length() == 1)
            emit fileDropped(urls[0], getDroppingItemIndex(event->position()));
        else if(urls.length() > 1)
            emit filesDropped(urls, getDroppingItemIndex(event->position()));
    }
    QListWidget::dropEvent(event);
}

void PlayListWidget::dragMoveEvent(QDragMoveEvent * e)
{
    e->acceptProposedAction();
    QListWidget::dragMoveEvent(e);
    dropIndicatorLine.beginningPoint = getDropIndicatorPosition(e->position());
    dropIndicatorLine.width = dropIndicatorLine.beginningPoint.x() + width();
    //qDebug()<<"Dropping item index:" << getDroppingItemIndex(e->position());
    viewport()->update();
}

void PlayListWidget::paintEvent(QPaintEvent * event)
{
    QListWidget::paintEvent(event);

    if(dropIndicatorLine.active) {
        QPainter painter(viewport());

        //QPoint pos = mapFromGlobal(QCursor::pos());

        painter.setPen(Qt::red);
        painter.drawLine(dropIndicatorLine.beginningPoint.x(), dropIndicatorLine.beginningPoint.y(), dropIndicatorLine.beginningPoint.x() + dropIndicatorLine.width, dropIndicatorLine.beginningPoint.y());
    }
}

QPointF PlayListWidget::getDropIndicatorPosition(const QPointF &mousePosition)
{
    QPointF dropIndicatorPosition;
    QListWidgetItem * currentItem = itemAt(mousePosition.toPoint());
    if(currentItem == nullptr)
        currentItem = item(count()-1);
    QRect itemRect = visualItemRect(currentItem);
    //qDebug()<<"Item rect:"<<itemRect << "Mouse Pos:" <<mousePosition;
    dropIndicatorPosition.setX(0);
    if(isDropIndicatorOnTopOrBottom(itemRect, mousePosition))
        dropIndicatorPosition.setY(itemRect.top());
    else
        dropIndicatorPosition.setY(itemRect.bottom()+1);
    return dropIndicatorPosition;
}

int PlayListWidget::getDroppingItemIndex(const QPointF &mousePosition)
{
    QPointF dropIndicatorPosition;
    QListWidgetItem * currentItem = itemAt(mousePosition.toPoint());
    if(currentItem == nullptr)
        currentItem = item(count()-1);
    int overIndex = indexFromItem(currentItem).row();
    int index;
    QRect itemRect = visualItemRect(currentItem);
    qDebug()<<"Item rect:"<<itemRect << "Mouse Pos:" <<mousePosition;
    dropIndicatorPosition.setX(0);
    if(isDropIndicatorOnTopOrBottom(itemRect, mousePosition))
        index = overIndex;
    else
            index = overIndex+1;
    return index;
}

bool PlayListWidget::isDropIndicatorOnTopOrBottom(const QRect & itemRectangle, const QPointF & mousePosition)
{
    return (itemRectangle.bottom() - mousePosition.y() -1 > mousePosition.y() - itemRectangle.top());
}
