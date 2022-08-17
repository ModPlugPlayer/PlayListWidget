/*
PlayListWidget definitions of PlayListWidget
Copyright (C) 2022 Volkan Orhan

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

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
    //qDebug()<<"RowIndex:"<<rowIndex;

    model()->insertRow(rowIndex);

    QListWidgetItem *insertedItem = item(rowIndex);

    PlayListItemWidget *playlistItemWidget = new PlayListItemWidget(this, playListItem);
    insertedItem->setSizeHint(playlistItemWidget->minimumSizeHint());

    setItemWidget(insertedItem, playlistItemWidget);
    updateItemNumbers();
}

void PlayListWidget::addPlayListItems(const QList<PlayListItem> & playListItems, int rowIndex)
{
    if(rowIndex == -1)
        rowIndex = count();
    //qDebug()<<"RowIndex:"<<rowIndex;
    for(const PlayListItem &playListItem:playListItems) {
        model()->insertRow(rowIndex);

        QListWidgetItem *insertedItem = item(rowIndex);

        PlayListItemWidget *playlistItemWidget = new PlayListItemWidget(this, playListItem);
        insertedItem->setSizeHint(playlistItemWidget->minimumSizeHint());

        setItemWidget(insertedItem, playlistItemWidget);
        rowIndex++;
    }
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

PlayListItem PlayListWidget::getCurrentItem()
{
    if(currentItem != nullptr)
        return currentItem->getData();
    else {
        PlayListItem playListItem;
        return playListItem;
    }
}

void PlayListWidget::onPlay() {
    if(currentItem == nullptr)
        return;
}

void PlayListWidget::onPlay(PlayListItem playListItem)
{
    if(currentItem == nullptr)
        return;
}

void PlayListWidget::onPause() {
    if(currentItem == nullptr)
        return;
}

void PlayListWidget::onResume() {
    if(currentItem == nullptr)
        return;
}

void PlayListWidget::onStop() {
    if(currentItem == nullptr)
        return;
}

void PlayListWidget::onNextSong() {
    if(currentItem == nullptr)
        return;
}

void PlayListWidget::onPreviousSong() {
    if(currentItem == nullptr)
        return;
}

void PlayListWidget::onClear()
{
    QListWidget::clear();
}

void PlayListWidget::dragEnterEvent(QDragEnterEvent * event)
{
    dropIndicator.setActive(true);
    viewport()->update();
    QListWidget::dragEnterEvent(event);
    event->acceptProposedAction();
}

void PlayListWidget::dragLeaveEvent(QDragLeaveEvent * event)
{
    dropIndicator.setActive(false);
    viewport()->update();
    QListWidget::dragLeaveEvent(event);
    event->accept();
}

void PlayListWidget::dropEvent(QDropEvent * event)
{
    dropIndicator.setActive(false);
    viewport()->update();
    if (event->mimeData()->hasUrls()) {
        QList<QUrl> urls = event->mimeData()->urls();
        if(urls.length() == 1)
            emit fileDropped(urls[0], getDroppingItemDestinationIndex(event->position()));
        else if(urls.length() > 1)
            emit filesDropped(urls, getDroppingItemDestinationIndex(event->position()));
        //qDebug()<<"Items dropped at index "<< getDroppingItemDestinationIndex(event->position());
    }
    if(!event->mimeData()->hasUrls() //file drop is not checked whether the drop is valid or not
            && !isValidDrop(event->position()))
        return;
    QListWidget::dropEvent(event);
    updateItemNumbers();
    event->acceptProposedAction();
}

void PlayListWidget::dragMoveEvent(QDragMoveEvent * e)
{
    QListWidget::dragMoveEvent(e);

    if(!e->mimeData()->hasUrls())
        dropIndicator.setActive(isValidDrop(e->position()));

    dropIndicator.setBeginningPoint(getDropIndicatorPosition(e->position()));
    dropIndicator.setWidth(dropIndicator.getBeginningPoint().x() + width());
    //qDebug()<<"Dropping item index:" << getDroppingItemIndex(e->position());
    viewport()->update();
    e->acceptProposedAction();
}

void PlayListWidget::paintEvent(QPaintEvent * event)
{
    QListWidget::paintEvent(event);

    if(dropIndicator.isActive()) {
        QPainter painter(viewport());
        dropIndicator.paint(painter);
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

int PlayListWidget::getDroppingItemDestinationIndex(const QPointF &mousePosition)
{
    QListWidgetItem * currentItem = itemAt(mousePosition.toPoint());
    if(currentItem == nullptr)
        currentItem = item(count()-1);
    int overIndex = indexFromItem(currentItem).row();
    int index;
    QRect itemRect = visualItemRect(currentItem);
    //qDebug()<<"Item rect:"<<itemRect << "Mouse Pos:" <<mousePosition;
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

bool isAdjacent(const QList<int> &list) {
    int len = list.count();
    if(len == 0 || len == 1)
        return false;
    int previousElement = list[0];
    for(int i=1; i<len; i++) {
        if(list[i] - previousElement != 1)
            return false;
        previousElement = list[i];
    }
    return true;
}

bool PlayListWidget::isValidDrop(const QPointF &dropPosition)
{
    if(selectedIndexes().isEmpty())
        return false;
    int droppedItemDestinationIndex = getDroppingItemDestinationIndex(dropPosition);
    int draggedItemIndex = currentIndex().row();
    if(selectedIndexes().count() == 1) {
        int itemIndexDifference = droppedItemDestinationIndex - draggedItemIndex;
        //qDebug()<<"Item index diff "<<itemIndexDifference;
        if(itemIndexDifference == 1 || itemIndexDifference == 0)
            return false;
        else
            return true;
    }
    QList<int> selectedIndices;
    for(const QModelIndex &currentIndex : selectedIndexes()) {
        selectedIndices.append(currentIndex.row());
    }
    std::sort(selectedIndices.begin(), selectedIndices.end());
    int beginningDifference = droppedItemDestinationIndex - selectedIndices[0];
    int endingDifference = droppedItemDestinationIndex - selectedIndices[selectedIndices.length()-1];
    //qDebug()<<"Beginning difference "<<beginningDifference;
    //qDebug()<<"Ending difference "<<endingDifference;
    if(beginningDifference == 1)
        return false;
    if(isAdjacent(selectedIndices)) {
        qDebug()<<"Adjacent";
        if(endingDifference <= 1 && beginningDifference >= 0)
            return false;
    }
    return true;
}
