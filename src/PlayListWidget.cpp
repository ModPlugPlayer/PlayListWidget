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
#include "PlayListStyleSheets.hpp"

PlayListWidget::PlayListWidget(QWidget *parent)
    : QListWidget(parent)
{
    setAcceptDrops(true);
    QListWidget::setDropIndicatorShown(false);
    QObject::connect(this, &PlayListWidget::itemDoubleClicked, this, &PlayListWidget::onItemDoubleClicked);
    verticalScrollBar()->setStyleSheet(PlayListStyleSheets::scrollBar);
}

void PlayListWidget::addPlayListItem(const PlayListItem & playListItem, int rowIndex)
{
    const std::lock_guard<std::mutex> locker(listItemsLock);
    if(rowIndex == -1)
        rowIndex = count();
    //qDebug()<<"RowIndex:"<<rowIndex;

    model()->insertRow(rowIndex);

    QListWidgetItem *insertedItem = item(rowIndex);

    PlayListItemWidget *playlistItemWidget = new PlayListItemWidget(this, playListItem);
    connectPlayListItemSignals(*playlistItemWidget);
    insertedItem->setSizeHint(playlistItemWidget->minimumSizeHint());
    playListMap[playListItem.id] = playlistItemWidget;

    setItemWidget(insertedItem, playlistItemWidget);
    updateItemNumbers();
}

void PlayListWidget::addPlayListItems(const QList<PlayListItem> & playListItems, int rowIndex)
{
    const std::lock_guard<std::mutex> locker(listItemsLock);
    if(rowIndex == -1)
        rowIndex = count();
    for(const PlayListItem &playListItem:playListItems) {
        model()->insertRow(rowIndex);

        QListWidgetItem *insertedItem = item(rowIndex);

        PlayListItemWidget *playlistItemWidget = new PlayListItemWidget(this, playListItem);
        connectPlayListItemSignals(*playlistItemWidget);
        insertedItem->setSizeHint(playlistItemWidget->minimumSizeHint());

        playListMap[playListItem.id] = playlistItemWidget;

        setItemWidget(insertedItem, playlistItemWidget);
        rowIndex++;
    }
    updateItemNumbers();
}

void PlayListWidget::removeSelectedItems()
{
    const std::lock_guard<std::mutex> locker(listItemsLock);
    QList<QListWidgetItem*> itemsToBeRemoved = selectedItems();
    if(itemsToBeRemoved.isEmpty())
        return;
    QList<int> itemIndicesToBeRemoved;
    for(QListWidgetItem* currentItem:itemsToBeRemoved) {
        PlayListItemWidget *playListItemWidget = dynamic_cast<PlayListItemWidget*>(itemWidget(currentItem));
        disconnectPlayListItemSignals(*playListItemWidget);
        itemIndicesToBeRemoved.append(playListItemWidget->getItemNumber());
    }
    std::sort(itemIndicesToBeRemoved.begin(), itemIndicesToBeRemoved.end(), std::greater<>());
    for(int i:itemIndicesToBeRemoved) {
        QListWidgetItem* currentItem = item(i);
        PlayListItemWidget *playListItemWidget = dynamic_cast<PlayListItemWidget*>(itemWidget(currentItem));
        playListMap.remove(playListItemWidget->getData().id);
        model()->removeRow(i);
        delete playListItemWidget;
    }
    updateItemNumbers();
}

PlayListItem PlayListWidget::getCurrentItem()
{
    const std::lock_guard<std::mutex> locker(listItemsLock);
    PlayListItem playListItem;
    if(currentItem != nullptr)
        playListItem = currentItem->getData();
    return playListItem;
}

void PlayListWidget::onMetaData(const PlayListItem playListItem) {

}

void PlayListWidget::onOpen(const PlayListItem playListItem) {

}

void PlayListWidget::onPlay(const PlayListItem playListItem) {
    const std::lock_guard<std::mutex> locker(listItemsLock);
    if(currentItem != nullptr)
        currentItem->setStatus(PlayingStatus::Stopped);

    currentItem = playListMap[playListItem.id];

    if(currentItem != nullptr)
        currentItem->setStatus(PlayingStatus::Playing);
}

void PlayListWidget::onPause(const PlayListItem playListItem) {
    if(!playListMap.contains(playListItem.id))
        return;
    PlayListItemWidget * playListItemWidget = playListMap[playListItem.id];
    playListItemWidget->setStatus(PlayingStatus::Paused);

}

void PlayListWidget::onResume(const PlayListItem playListItem) {
    if(!playListMap.contains(playListItem.id))
        return;
    PlayListItemWidget * playListItemWidget = playListMap[playListItem.id];
    playListItemWidget->setStatus(PlayingStatus::Playing);
}

void PlayListWidget::onStop(const PlayListItem playListItem) {
    if(!playListMap.contains(playListItem.id))
        return;
    PlayListItemWidget * playListItemWidget = playListMap[playListItem.id];
    playListItemWidget->setStatus(PlayingStatus::Stopped);
}

void PlayListWidget::onNextSong() {
    if(currentItem == nullptr)
        return;
    size_t itemNumber = currentItem->getItemNumber();
    size_t itemAmount = (size_t) count();
    if(itemAmount < 2)
        return;
    QListWidgetItem *nextWidgetItem;

    if(itemNumber > itemAmount - 2) {
        if(repeatState != RepeatState::PlayList)
            return;
        nextWidgetItem = item(0);
    }
    else {
        nextWidgetItem = item(itemNumber+1);
    }

    currentItem->setStatus(PlayingStatus::Stopped);

    scrollToItemIfNeeded(nextWidgetItem);

    PlayListItemWidget *nextPlayListItemWidget = dynamic_cast<PlayListItemWidget*>(itemWidget(nextWidgetItem));
    emit play(nextPlayListItemWidget->getData());
}

void PlayListWidget::onPreviousSong() {
    if(currentItem == nullptr)
        return;
    size_t itemNumber = currentItem->getItemNumber();
    size_t itemAmount = (size_t) count();

    QListWidgetItem *previousWidgetItem;

    if(itemNumber < 1) {
        if(repeatState != RepeatState::PlayList)
            return;
        previousWidgetItem = item(itemAmount-1);
    }
    else {
        previousWidgetItem = item(itemNumber-1);
    }

    currentItem->setStatus(PlayingStatus::Stopped);

    scrollToItemIfNeeded(previousWidgetItem);

    PlayListItemWidget *previousPlayListItemWidget = dynamic_cast<PlayListItemWidget*>(itemWidget(previousWidgetItem));
    emit play(previousPlayListItemWidget->getData());
}

void PlayListWidget::onClear()
{
    QListWidget::clear();
}

void PlayListWidget::onRepeat(const RepeatState repeatState)
{
    this->repeatState = repeatState;
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

void PlayListWidget::scrollToItemIfNeeded(QListWidgetItem *listWidgetItem)
{
    QRect itemRect = visualItemRect(listWidgetItem);
    QRect rect = contentsRect();

    if(itemRect.top() < rect.top())
        scrollToItem(listWidgetItem, PositionAtTop);
    else if(itemRect.bottom() > rect.bottom())
        scrollToItem(listWidgetItem, PositionAtBottom);
}

void PlayListWidget::onItemDoubleClicked(QListWidgetItem *item)
{
    PlayListItemWidget * widget = dynamic_cast<PlayListItemWidget*>(itemWidget(item));
    PlayListItem playListItem = widget->getData();
    emit play(widget->getData());
    qDebug()<<"Item double clicked " << widget->getFilePath().c_str();
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
    bool listItemsLockIsAlreadyLocked = !listItemsLock.try_lock();

    int len = count();
    for(int i=0; i<len; i++) {
        QListWidgetItem * currentItem = item(i);
        PlayListItemWidget *playListItemWidget = dynamic_cast<PlayListItemWidget*>(itemWidget(currentItem));
        if(playListItemWidget->getItemNumber() != i)
            playListItemWidget->setItemNumber(i);
    }
    //static int updateNo = 1;
    //qDebug()<<"Update " + QString::number(updateNo++);
    if(!listItemsLockIsAlreadyLocked)
        listItemsLock.unlock();
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

void PlayListWidget::connectPlayListItemSignals(PlayListItemWidget &playListItemWidget) {
    QObject::connect(&playListItemWidget, &PlayListItemWidget::pause, this, &PlayListWidget::pause);
    QObject::connect(&playListItemWidget, &PlayListItemWidget::resume, this, &PlayListWidget::resume);
    QObject::connect(&playListItemWidget, &PlayListItemWidget::play, this, &PlayListWidget::play);

}

void PlayListWidget::disconnectPlayListItemSignals(PlayListItemWidget &playListItemWidget) {
    QObject::disconnect(&playListItemWidget, &PlayListItemWidget::pause, this, &PlayListWidget::pause);
    QObject::disconnect(&playListItemWidget, &PlayListItemWidget::resume, this, &PlayListWidget::resume);
    QObject::disconnect(&playListItemWidget, &PlayListItemWidget::play, this, &PlayListWidget::play);
}
