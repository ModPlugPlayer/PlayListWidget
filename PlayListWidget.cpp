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

    model()->insertRow(rowIndex);

    QListWidgetItem *insertedItem = item(rowIndex);

    PlayListItemWidget *playlistItemWidget = new PlayListItemWidget(this, playListItem);
    insertedItem->setSizeHint(playlistItemWidget->minimumSizeHint());

    setItemWidget(insertedItem, playlistItemWidget);
    updateItemNumbers();
}

void PlayListWidget::removeSelectedItems()
{
    QList<QListWidgetItem*> itemsToBeRemoved = selectedItems();
    if(itemsToBeRemoved.isEmpty())
        return;
    QList<int> itemIndicesToBeRemoved;
    for(QListWidgetItem* currentItem:itemsToBeRemoved) {
        PlayListItemWidget *playListItemWidget = dynamic_cast<PlayListItemWidget*>(itemWidget(currentItem));
        itemIndicesToBeRemoved.append(playListItemWidget->getItemNumber());
    }
    std::sort(itemIndicesToBeRemoved.begin(), itemIndicesToBeRemoved.end(), std::greater<>());
    for(int i:itemIndicesToBeRemoved) {
        QListWidgetItem* currentItem = item(i);
        //removeItemWidget(currentItem);
        model()->removeRow(i);
        PlayListItemWidget *playListItemWidget = dynamic_cast<PlayListItemWidget*>(itemWidget(currentItem));
        delete playListItemWidget;
    }
    updateItemNumbers();
}

void PlayListWidget::dragEnterEvent(QDragEnterEvent * event)
{
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
    event->acceptProposedAction();
    updateItemNumbers();
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
    //qDebug()<<"Item rect:"<<itemRect << "Mouse Pos:" <<mousePosition;
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

void PlayListWidget::updateItemNumbers()
{
    int len = count();
    for(int i=0; i<len; i++) {
        QListWidgetItem * currentItem = item(i);
        PlayListItemWidget *playListItemWidget = dynamic_cast<PlayListItemWidget*>(itemWidget(currentItem));
        if(playListItemWidget->getItemNumber() != i)
            playListItemWidget->setItemNumber(i);
    }
    //static int updateNo = 1;
    //qDebug()<<"Update " + QString::number(updateNo++);
}
